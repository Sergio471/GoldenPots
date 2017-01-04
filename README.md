# GoldenPots
Game with numbers.

There are pots with gold coins in them.
In order to win, you should collect more gold than AI does.
You and AI can collect gold only from left most or right most of the remaining pots.
At each step, row of numbers represents number of gold coins in pots.

# Technical details
There is a little disbalance in starting distribution of gold in pots.
The greater BALANCE_EPS in code, the greater disbalance.

Also, AI can make a 50% mistake if benefits of both moves differ slightly.
The greater MISTAKE_EPS in code, the less accurate is AI.

Set both *_EPS to 0.00 to make starting distribution of gold and AI perfect.
(In such case, it is impossible to win).

#Example of a game (human started)

Current State:  7 3 6 7 6 9 7 7 7 9
Player is taking: left

Current State:    3 6 7 6 9 7 7 7 9
AI is taking: right

Current State:    3 6 7 6 9 7 7 7  
Player is taking: right

Current State:    3 6 7 6 9 7 7    
AI is taking: right

Current State:    3 6 7 6 9 7      
Player is taking: right

Current State:    3 6 7 6 9        
AI is taking: right

Current State:    3 6 7 6          
Player is taking: right

Current State:    3 6 7            
AI is taking: right

Current State:    3 6              
Player is taking: right

Current State:    3                
AI is taking: left
Player score: 33
AI score: 35
