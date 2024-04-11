// 7.通过import的方式，引入Native能力。
import nativeModule from 'libentry.so'

@Entry
@Component
struct Index {
  @State message: string = 'Test Node-API callNative result: ';
  @State message2: string = 'Test Node-API nativeCallArkTS result: ';

  build() {
    Row() {
      Column() {
        // 第一个按钮，调用add方法，对应到Native侧的CallNative方法，进行两数相加。
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message += nativeModule.callNative(3, 4);
          })
        // 第二个按钮，调用nativeCallArkTS方法，对应到Native的NativeCallArkTS，在Native调用ArkTS function。
        Text(this.message2)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message2 += nativeModule.nativeCallArkTS((a: number) => {
              return a * 2;
            })
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}