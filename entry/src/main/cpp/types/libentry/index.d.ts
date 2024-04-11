// 3. 提供JS侧的接口方法
export const callNative: (a: number, b: number) => number;
export const nativeCallArkTS: (cb: (a: number) => number) => number;