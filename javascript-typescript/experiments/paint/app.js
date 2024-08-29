const CANVAS_SIZE = 500;

const sizeInput = document.getElementById("size");
const colorpicker = document.getElementById("colorpicker");
const strokeBtn = document.getElementById("stroke");
const fillBtn = document.getElementById("fill");
const eraserBtn = document.getElementById("eraser");
const backBtn = document.getElementById("back");
const resetBtn = document.getElementById("reset");
const downloadBtn = document.getElementById("download");

const canvas = document.getElementById("canvas");
canvas.width = CANVAS_SIZE;
canvas.height = CANVAS_SIZE;
const ctx = canvas.getContext("2d");

let isDown = false;
let isFilling = false;
let isErasing = false;
let currentSize = sizeInput.value;
let currentColor = "#000000";

let drawings = [];
let drawingBuffer = null;

sizeInput.addEventListener("change", (e) => {
    currentSize = e.target.value;
});

colorpicker.addEventListener("change", (e) => {
    currentColor = e.target.value;
});

strokeBtn.addEventListener("click", setStrokeMode);
fillBtn.addEventListener("click", setFillMode);
eraserBtn.addEventListener("click", setEraserMode);

resetBtn.addEventListener("click", () => {
    clearCanvas();
    drawings = [];
});

backBtn.addEventListener("click", () => {
    drawings.pop();
    updateCanvas();
});

window.addEventListener("keydown", (e) => {
    if (e.ctrlKey && e.key === "z") {
        backBtn.click();
    }
});

downloadBtn.addEventListener("click", () => {
    const a = document.createElement("a");
    a.href = canvas.toDataURL("image/png");
    a.download = "capture.png";
    a.click();
});

function convertHexToRgb(hex) {
    const red = parseInt(hex.substr(1, 2), 16);
    const green = parseInt(hex.substr(3, 2), 16);
    const blue = parseInt(hex.substr(5, 2), 16);
    return { red, green, blue, alpha: 255 };
}

function getMousePosition(e) {
    const rect = canvas.getBoundingClientRect();
    return {
        x: e.clientX - rect.left,
        y: e.clientY - rect.top,
    };
}

function setStrokeMode() {
    isFilling = false;
    isErasing = false;
    ctx.globalCompositeOperation = "source-over";
}

function setFillMode() {
    isFilling = true;
    isErasing = false;
    ctx.globalCompositeOperation = "source-over";
}

function setEraserMode() {
    isFilling = false;
    isErasing = true;
    ctx.globalCompositeOperation = "destination-out";
}

function clearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}

function startStroke(pos, size, color) {
    ctx.moveTo(pos.x, pos.y);
    ctx.beginPath();

    ctx.lineCap = "round";
    ctx.lineWidth = size;
    ctx.strokeStyle = color || currentColor;
}

function makeStroke(pos) {
    ctx.lineTo(pos.x, pos.y);
    ctx.stroke();
}

function endStroke() {
    if (drawingBuffer !== null) {
        drawings.push(drawingBuffer);
    }
    drawingBuffer = null;
    isDown = false;
}

function isValidPosition(pos) {
    return (
        pos.x >= 0 && pos.y >= 0 && pos.x < CANVAS_SIZE && pos.y < CANVAS_SIZE
    );
}

function isTargetColor(pos, targetPixelData) {
    const pixelData = ctx.getImageData(pos.x, pos.y, 1, 1).data;

    return (
        pixelData[0] === targetPixelData[0] &&
        pixelData[1] === targetPixelData[1] &&
        pixelData[2] === targetPixelData[2] &&
        pixelData[3] === targetPixelData[3]
    );
}

// Pure brute force (not ideal)
function fill(pos, color) {
    const targetPixelData = ctx.getImageData(pos.x, pos.y, 1, 1).data;

    ctx.fillStyle = color;
    ctx.fillRect(pos.x, pos.y, 1, 1);

    const queue = [pos];
    const cache = {};

    while (queue.length > 0) {
        const currPos = queue.shift();

        const neighborPositions = [
            { x: currPos.x + 1, y: currPos.y },
            { x: currPos.x - 1, y: currPos.y },
            { x: currPos.x, y: currPos.y + 1 },
            { x: currPos.x, y: currPos.y - 1 },
        ];

        for (const neighborPos of neighborPositions) {
            const key = neighborPos.x + ":" + neighborPos.y;
            if (
                !(key in cache) &&
                isValidPosition(neighborPos) &&
                isTargetColor(neighborPos, targetPixelData)
            ) {
                queue.push(neighborPos);
                ctx.fillRect(neighborPos.x, neighborPos.y, 1, 1);
            }
            cache[key] = true;
        }
    }
}

function updateCanvas() {
    clearCanvas();

    const wasErasing = isErasing;
    const wasFilling = isFilling;

    for (const drawing of drawings) {
        switch (drawing.type) {
            case "stroke": {
                setStrokeMode();
                startStroke(drawing.start, drawing.size, drawing.color);
                for (const pos of drawing.steps) {
                    makeStroke(pos);
                }
                break;
            }
            case "fill": {
                setFillMode();
                fill(drawing.start, drawing.color);
                break;
            }
            case "erase": {
                setEraserMode();
                startStroke(drawing.start, drawing.size);
                for (const pos of drawing.steps) {
                    makeStroke(pos);
                }
                break;
            }
        }
    }

    if (wasFilling) {
        setFillMode();
    } else if (wasErasing) {
        setEraserMode();
    } else {
        setStrokeMode();
    }
}

canvas.addEventListener("mousedown", (e) => {
    const pos = getMousePosition(e);

    if (isFilling) {
        drawingBuffer = {
            type: "fill",
            start: pos,
            color: currentColor,
        };
        return fill(pos, currentColor);
    }

    isDown = true;
    startStroke(pos, currentSize, currentColor);

    if (isErasing) {
        drawingBuffer = {
            type: "erase",
            start: pos,
            size: currentSize,
            steps: [],
        };
    } else {
        drawingBuffer = {
            type: "stroke",
            start: pos,
            size: currentSize,
            color: currentColor,
            steps: [],
        };
    }
});

canvas.addEventListener("mousemove", (e) => {
    if (isDown) {
        const pos = getMousePosition(e);

        makeStroke(pos);

        drawingBuffer.steps.push(pos);
    }
});

canvas.addEventListener("mouseup", endStroke);
canvas.addEventListener("mouseleave", endStroke);
