import { World } from './classes/world';
import { BLUR, FADE, HEIGHT, N, WIDTH } from './settings';

const world = new World(N);

const canvas = document.getElementsByTagName('canvas')[0];
canvas.width = WIDTH;
canvas.height = HEIGHT;
const ctx = canvas.getContext('2d');

const copy = document.createElement('canvas');
copy.width = WIDTH;
copy.height = HEIGHT;
const utx = copy.getContext('2d');
utx.filter = `blur(${BLUR}px)`;
utx.globalAlpha = 1 - FADE;

const refresh = () => {
  utx.clearRect(0, 0, WIDTH, HEIGHT);
  utx.drawImage(canvas, 0, 0);

  ctx.clearRect(0, 0, WIDTH, HEIGHT);
  ctx.drawImage(copy, 0, 0);

  world.advance(ctx);

  ctx.fillStyle = 'white';
  world.draw(ctx);

  requestAnimationFrame(() => refresh());
};
refresh();
