import { HEIGHT, WIDTH } from '../settings';
import { Cell } from './cell';

export class World {
  private cells: Cell[] = [];

  constructor(n: number) {
    this.cells = new Array(n)
      .fill(null)
      .map((_, i) => new Cell(WIDTH / 2, HEIGHT / 2, i / n));
  }

  advance(ctx: CanvasRenderingContext2D): void {
    this.cells.forEach(cell => cell.advance(ctx));
  }

  draw(ctx: CanvasRenderingContext2D): void {
    this.cells.forEach(cell => cell.draw(ctx));
  }
}
