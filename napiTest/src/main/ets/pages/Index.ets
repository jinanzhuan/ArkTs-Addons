import { hilog } from '@kit.PerformanceAnalysisKit';
import testNapi from 'libnapitest.so';
import {MyObject} from 'libnapitest.so';



@Entry
@Component
struct Index {
  @State message: string = 'Hello, I am Harmony' ;
  @State message2: string = 'Hello, add method' ;
  @State message3: string = 'Hello, callback from native' ;
  @State message4: string = 'Hello, object from native' ;
  @State message5: string = 'Hello, ObjectWrapper from native' ;

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(25)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message = 'testNapi.hello(): '+testNapi.hello();
          })
        Blank(10)
        Text(this.message2)
          .fontSize(25)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message2 = 'Test NAPI 2 + 3 = '+testNapi.add(2, 3);
          })
        Blank(10)
        Text(this.message3)
          .fontSize(25)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.message3 = testNapi.nativeCallback((a:string) => {
              return a
            })
          })
        Blank(10)
        Text(this.message4)
          .fontSize(25)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let object = testNapi.createObject('Hello');
            let object2 = testNapi.createObject('world');
            this.message4 = object.msg + ' ' + object2.msg;
          })
        Blank(10)
        Text(this.message5)
          .fontSize(25)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            let object = new MyObject(10);
            console.log( object.plusOne().toString());
            console.log( object.plusOne().toString());
            console.log( object.plusOne().toString());

            console.log( object.multiply(1).value());
            console.log( object.multiply(10).value());
            this.message5 = 'has MyObject result'
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
