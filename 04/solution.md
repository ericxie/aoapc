## 04 函数与递归

推荐： UVA133 

坑题： UVA489，UVA213

---

### UVA-1339 Anciet Cipher

题意： 判断a串是否是b串的替换和置换加密的密码。

替换和置换加密不会改变词频，所以统计两个串的词频，比较即可。

[code](./uva1339.cpp)


### UVA-489 Hangman Game

题意：猜字符串的字符游戏，错不能超过7次。

坑题！重复错的只算1次（这个好歹题面还有讲，不算坑）！神坑就是如果赢了后面再猜不算错！！！。

标记数组，1表示字符出现过，0表示字符没有出现过， -1 表示字符已经被猜。统计所有的字符数total和统计错误次数，模拟即可。

[code](./uva489.cpp)

### UVA-133 The Dole Queue

题意： 顺时钟和逆时钟的约瑟夫环模拟。

手敲一个双向循环的队列，注意删除点相邻的时候的下标修改即可。

[code](./uva133.cpp)


### UVA-213 Message Decoding 

题意： 一个文本串，按下标编码为"0","00","01","10","000",...。 全1为停止标志。读入一个二进制串，二进制串由多段组成，每段开头3位是宽度，然后是若干个信息编码，到停止标志为止。要求进行译码。

垃圾题目，输入很恶心，阅读题，题意上说以停止标志为段结束，输入样例里最后一段是没有停止标志的。
题目不说文本串的组成（万一文本串有0或者1了？）和所有串的大小，只能去猜，UVA的题对C太不友好了。

[code](./uva213.cpp)

### UVA-512 Spreadsheet Tracking

题意： 给一个表格，有5种命令，插入行，列，删除行列，交换两个单元格。n条指令，m次查询，查询原始单元格(x,y)的最终坐标。

没给n和m的数据范围，按UVA一贯的尿性，没给就是可以暴力。离线做的，对于每次查询，执行n条指令，判结果就可。

[code](./uva512.cpp)


### UVA-12412 A Typical Homework

题意： 做个成绩管理系统...

大模拟，~~暂时鸽了。~~ 

按题意做即可，注意处理输入时，最好不用gets和scanf混合，容易错。课程统计时，如果符合条件的人数为0，那么输出0.00。

[code](./uva12412.cpp)





