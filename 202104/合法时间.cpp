给你一个字符串 time ，格式为 hh:mm（小时：分钟），其中某几位数字被隐藏（用 ? 表示）。

有效的时间为 00:00 到 23:59 之间的所有时间，包括 00:00 和 23:59 。

替换 time 中隐藏的数字，返回你可以得到的最晚有效时间。

 

示例 1：

输入：time = "2?:?0"
输出："23:50"
解释：以数字 '2' 开头的最晚一小时是 23 ，以 '0' 结尾的最晚一分钟是 50 。
示例 2：

输入：time = "0?:3?"
输出："09:39"
示例 3：

输入：time = "1?:22"
输出："19:22"

  
  class Solution {
public:
    string maximumTime(string time) {

       if(time[0]=='?'&&time[1]=='?')
       {
           time[0]='2';
           time[1]='3';
       }
       else if(time[0]=='?')
       {
           if(time[1]>='0'&&time[1]<='3')
           {
                 time[0]='2';
           }
           else{
                time[0]='1';
           }
       }
       else if(time[1]=='?')
       {
         if(time[0]<'2')
        {
            time[1]='9';
        }
         else
         {
             time[1]='3';
         }
       }
     
           if(time[3]=='?')
            time[3]='5';
           if(time[4]=='?')
           time[4]='9';
       
       return time;
    }
};
