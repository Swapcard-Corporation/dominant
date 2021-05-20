import { ofUrl } from '../src/Dominant.bs';

const dominantColors = ofUrl('https://www.swapcard.com/');

function component() {
  const element = document.createElement('div');
  console.log('dominantColors are: ', dominantColors);
  // Lodash, currently included via a script, is required for this line to work

  // Lodash, now imported by this script
  element.innerHTML = "Hello, SwapCard";

  return element;
}

document.body.appendChild(component());
