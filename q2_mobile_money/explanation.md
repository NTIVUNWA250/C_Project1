# Question 2: How the control flow works

## Data types

I used `long` for the currents as RWF doesn't have cents and also long gives enough room for the numbers in integers more than `int` could do. The menu is in `int` as it can be used in the `switch`. The `int running` flag is the one that controls `main loop`.

## Loop

We used a `while loop` and everything happens inside it. Each pass prints the prompt, reads a choice and handles it. The loop only ends when the agent picks option 5, which sets `running` to 0. There is no fixed number of passes, which is the point: the agent can do as many transactions as they like without restarting the program. 

## Conditionals

We used `switch` for all conditions and each one has its own case with a default when the user chooses numbers that are not in the program. If conditions are used to confirm validation. A negative and zero amounts are refused for withdrawal and deposit. Withdrawal also reject the amount if it is larger than the balance that we have. When all the checks are validated, then the transaction is accepted and balance is given.

## Continue
It is used when the user input is unusable. The input is clear, gives the message to the user and prompts them by putting a better input using `continue`. This is also used in the default when the user entres a number that is not between 1 and 5.

## break

`break` appears in two roles. Inside the `switch`, every case ends with `break` so that the program does not fall through into the next case. The early `break` statements after a rejected transaction also stop the rest of that case from running, so a refused withdrawal never touches the balance. In the Exit case, `break` leaves the `switch` after `running` has been set to 0, and the `while` condition then ends the loop. I preferred the flag over a bare `break` out of the loop because `break` inside a `switch` only exits the `switch`, which is an easy mistake to make.

## Logging

Every accepted or rejected transaction is then recorded in the `transactions.log` with the amount and the balance being recorded after the transation. This does not stop the program from working when the file cannot be opened.

