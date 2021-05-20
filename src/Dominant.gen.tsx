/* TypeScript file generated from Dominant.re by genType. */
/* eslint-disable import/first */


// @ts-ignore: Implicit any on import
import * as Curry__Es6Import from 'bs-platform/lib/es6/curry.js';
const Curry: any = Curry__Es6Import;

// @ts-ignore: Implicit any on import
import * as DominantBS__Es6Import from './Dominant.bs';
const DominantBS: any = DominantBS__Es6Import;

// tslint:disable-next-line:interface-over-type-literal
export type pixel = {
  readonly red: number; 
  readonly green: number; 
  readonly blue: number
};

export const ofUrl: (url:string, _2:{ readonly square?: number }, param:void) => Promise<pixel[]> = function (Arg1: any, Arg2: any, Arg3: any) {
  const result = Curry._3(DominantBS.ofUrl, Arg1, Arg2.square, Arg3);
  return result
};
