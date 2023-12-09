import express from "express";
import multer from "multer";
import fs from "fs";

const PORT = 8080;

const app = express();

app.set("view engine", "ejs");

const upload = multer({
    storage: multer.diskStorage({
        destination: "uploads/",
        filename: (_req, file, cb) => {
            cb(null, file.originalname);
        },
    }),
});

app.get("/", (_req, res) => {
    const videos = fs.readdirSync("uploads");
    return res.render("index", { videos });
});

app.post("/videos", upload.single("video"), (_req, res) => {
    return res.redirect("/");
});

app.get("/videos/:name", (req, res) => {
    return res.render("stream", { video: req.params.name });
});

app.get("/videos/:name/stream", (req, res) => {
    const range = req.headers.range;

    if (!range) return res.status(400).send("Range header required");

    const videoName = req.params.name;
    const videoPath = "uploads/" + videoName;
    const videoSize = fs.statSync(videoPath).size;

    const CHUNK_SIZE = 10 ** 6; // 1 MB
    const start = Number(range.replace(/\D/g, ""));
    const end = Math.min(start + CHUNK_SIZE, videoSize - 1);

    const headers = {
        "Accept-Ranges": "bytes",
        "Content-Range": `bytes ${start}-${end}/${videoSize}`,
        "Content-Length": end - start + 1,
        "Content-Type": "video/mp4",
    };

    res.writeHead(206, headers);

    const videoStream = fs.createReadStream(videoPath, { start, end });

    videoStream.pipe(res);
});

app.listen(PORT, () => {
    console.log("Server listening on port " + PORT);
});
