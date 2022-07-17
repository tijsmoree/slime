import {
  BOUNCEANGLE,
  HEIGHT,
  SIGHT,
  SIGHTANGLE,
  SIZE,
  SPEED,
  SWING,
  WIDTH,
} from '../settings';

export class Cell {
  constructor(private x: number, private y: number, private a: number) {}

  advance(ctx: CanvasRenderingContext2D): void {
    const [left, right] = [-1, 1]
      .map(x => x * SIGHTANGLE + this.a)
      .map(a =>
        ctx.getImageData(
          Math.round(this.x + Math.cos(a * 2 * Math.PI) * SIGHT),
          Math.round(this.y + Math.sin(a * 2 * Math.PI) * SIGHT),
          1,
          1,
        ),
      )
      .map(x => x.data[3]);

    if (left !== right) {
      this.a += (left > right ? -1 : 1) * SWING;
    }

    this.x += Math.cos(this.a * 2 * Math.PI) * SPEED;
    this.y += Math.sin(this.a * 2 * Math.PI) * SPEED;

    if (this.x < 0) {
      this.a = (Math.random() - 1) * BOUNCEANGLE;
    } else if (this.y < 0) {
      this.a = (Math.random() - 1) * BOUNCEANGLE + 0.25;
    } else if (this.x > WIDTH) {
      this.a = (Math.random() - 1) * BOUNCEANGLE + 0.5;
    } else if (this.y > HEIGHT) {
      this.a = (Math.random() - 1) * BOUNCEANGLE + 0.75;
    }
  }

  draw(ctx: CanvasRenderingContext2D): void {
    ctx.beginPath();
    ctx.arc(this.x, this.y, SIZE, 0, Math.PI * 2);
    ctx.fill();
  }
}
