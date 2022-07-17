import { HEIGHT, WIDTH } from '../settings';
import { Cell } from './cell';

export class World {
  private cells: Cell[] = [];

  constructor(n: number) {
    const min = Math.min(WIDTH / 2, HEIGHT / 2);

    this.cells = new Array(n).fill(null).map((_, i) => {
      const x = Math.random() * WIDTH;
      const y = Math.random() * HEIGHT;
      const a = Math.atan2(HEIGHT / 2 - y, WIDTH / 2 - x) / 2 / Math.PI;

      return new Cell(x, y, a);
    });
  }

  advance(ctx: CanvasRenderingContext2D): void {
    this.cells.forEach(cell => cell.advance(ctx));
  }

  draw(ctx: CanvasRenderingContext2D): void {
    this.cells.forEach(cell => cell.draw(ctx));
  }
}
