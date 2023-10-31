function randomNumberUpTo(max) {
  return Math.round(Math.random() * max);
}

function randomNumberFromRange(min, max) {
  return Math.round(Math.random() * (max - min) + min);
}

class RandomParticle {
  constructor(x, y, minRadius = 10, maxRadius = 20) {
    this.coordinate = {
      x,
      y,
    };
    this.direction = {
      x: Math.random() < 0.5 ? -1 : 1,
      y: Math.random() < 0.5 ? -1 : 1,
    };
    this.radius = randomNumberFromRange(minRadius, maxRadius);
    this.color = this.generateRandomRGBAColor();
  }

  generateRandomRGBAColor() {
    const red = randomNumberUpTo(255);
    const green = randomNumberUpTo(255);
    const blue = randomNumberUpTo(255);
    const alpha = randomNumberUpTo(10) / 10;

    return `rgba(${red}, ${green}, ${blue}, ${alpha})`;
  }

  draw(ctx) {
    this.ctx = ctx;

    ctx.beginPath();
    ctx.arc(
      this.coordinate.x,
      this.coordinate.y,
      this.radius,
      0,
      Math.PI * 2,
      false
    );
    ctx.closePath();

    ctx.fillStyle = this.color;
    ctx.fill();
  }

  move(canvasWidth, canvasHeight) {
    this.coordinate.x += this.direction.x;
    this.coordinate.y += this.direction.y;

    if (this.coordinate.x >= canvasWidth || this.coordinate.x <= 0) {
      this.direction.x = -this.direction.x;
    }

    if (this.coordinate.y < 0 || this.coordinate.y > canvasHeight) {
      this.direction.y = -this.direction.y;
    }

    this.draw(this.ctx);
  }
}

const canvas = document.querySelector("#canvas");
const canvasCtx = canvas.getContext("2d");

const circles = [];

for (let i = 0; i < 100; i++) {
  const particle = new RandomParticle(
    Math.random() * canvas.width,
    Math.random() * canvas.height,
    30,
    50
  );
  circles.push(particle);
  particle.draw(canvasCtx);
}

function animate() {
  canvasCtx.clearRect(0, 0, canvas.width, canvas.height);

  for (const circle of circles) {
    circle.move(canvas.width, canvas.height);
  }

  requestAnimationFrame(animate);
}

animate();
