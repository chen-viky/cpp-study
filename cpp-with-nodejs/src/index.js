let obj = require("../build/Debug/native.node");
console.log("hello", obj.hello());
console.log("add", obj.add(1, 2, 3, 4, 5, 6, 7, 8, 9)); //输出add 45
let param = {
  timeSpan: 6,
  callBack: (err, result) => {
    if (err) {
      console.log("callback an error: ", err);
    } else {
      console.log("callback array:" + result);
    }
  },
};
let result = obj.asyncMethod(param);
console.log("asyncMethod", result);
param.timeSpan = 4;
result = obj.asyncMethod(param);
console.log("asyncMethod", result);
