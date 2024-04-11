import { constant } from "@kit.ConnectivityKit";

export const add: (a: number, b: number) => number;
export const hello: () => string;
export const nativeCallback: (cb: (a: string) => string) => string;
export class StringObject {
  public get msg(): string;
}
export const createObject: (a: string) => StringObject;

export class MyObject {
  constructor(arg: number)

  plusOne: () => number;
  multiply: (a: number|undefined) => MyObject;

  public get value();
}
