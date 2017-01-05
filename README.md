# GoldenPots
Game with numbers.

There are pots with gold coins in them.
In order to win, you should collect more gold than AI does.
You and AI can collect gold only from left most or right most of the remaining pots.
At each step, row of numbers represents number of gold coins in pots.

#Setup and Run
```shell
./golden_pots [num_of_pots [max_gold_in_pot]]  
```
make  

Examples:  
```shell
./golden_pots 14 (14 pots with up to 10 gold coins in each)  
./golden_pots 15 19 (15 pots with up to 19 gold coins in each)  
```

# Technical details
There is a little disbalance in starting distribution of gold in pots.
The greater BALANCE_EPS in code, the greater is disbalance.

Also, AI can make a 50% mistake if benefits of both moves differ only slightly.
The greater MISTAKE_EPS in code, the less accurate is AI.

Set both *_EPS to 0.00 to make balance of starting distribution of gold and AI perfect.
(In such case, it is impossible to win).

#Example of a round (human started)

<img src="https://github.com/Sergio471/GoldenPots/blob/master/game_example.png" alt="Drawing" style="width: 120px; height: 100px;"/>
