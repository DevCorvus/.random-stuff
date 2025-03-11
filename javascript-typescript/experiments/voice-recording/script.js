const btn = document.getElementById("btn");
const capture = document.getElementById("capture");
const playback = document.getElementById("playback");
const download = document.getElementById("download");

class VoiceRecording {
    constructor() {
        this.setDefaultRecordingState();
    }

    setDefaultRecordingState() {
        this.audioStream = null;
        this.mediaRecorder = null;
        this.audioChunks = [];
    }

    get isRecording() {
        return this.audioStream !== null;
    }

    get isCapturing() {
        return this.mediaRecorder !== null;
    }

    stopAudioStream() {
        this.audioStream.getTracks().forEach((track) => track.stop());
    }

    async start({ playback, capture }) {
        if (!(navigator.mediaDevices && navigator.mediaDevices.getUserMedia)) {
            throw new Error("Not supported");
        }

        this.audioStream = await navigator.mediaDevices.getUserMedia({
            audio: true,
        });

        if (playback) {
            const audioContext = new AudioContext();
            const audioSource = audioContext.createMediaStreamSource(
                this.audioStream,
            );
            audioSource.connect(audioContext.destination);
        }

        if (capture) {
            this.mediaRecorder = new MediaRecorder(this.audioStream);

            this.mediaRecorder.addEventListener("dataavailable", (e) => {
                this.audioChunks.push(e.data);
            });

            this.mediaRecorder.start();
        }
    }

    async stop() {
        if (!this.isCapturing) {
            this.stopAudioStream();
            this.setDefaultRecordingState();
            return Promise.resolve(null);
        }

        const mimeType = this.mediaRecorder.mimeType;

        return new Promise((resolve) => {
            this.mediaRecorder.addEventListener("stop", () => {
                const audioBlob = new Blob(this.audioChunks, {
                    type: mimeType,
                });

                resolve(audioBlob);
            });

            this.mediaRecorder.stop();
            this.stopAudioStream();
            this.setDefaultRecordingState();
        });
    }
}

const voiceRecording = new VoiceRecording();

btn.addEventListener("click", async () => {
    if (!voiceRecording.isRecording) {
        await voiceRecording.start({
            capture: capture.checked,
            playback: playback.checked,
        });
        btn.textContent = "Stop Recording";
    } else {
        const audioBlob = await voiceRecording.stop();

        if (audioBlob) {
            const audioUrl = URL.createObjectURL(audioBlob);
            const audio = new Audio(audioUrl);

            btn.textContent = "Playing Recording...";
            btn.disabled = true;

            await audio.play();

            audio.addEventListener("ended", () => {
                btn.textContent = "Start Recording";
                btn.disabled = false;

                if (download.checked) {
                    const a = document.createElement("a");
                    a.href = audioUrl;
                    a.download = "recording.wav";
                    a.click();
                }
            });
        } else {
            btn.textContent = "Start Recording";
            btn.disabled = false;
        }
    }
});
