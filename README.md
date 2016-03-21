# myscheme
A Scheme Interpreter Using C++

词法：

`token` 			——> `identifer | number | boolean | string`

`identifer`		——> `inital subsequent*`

`inital` 			——> `letter | specialinital`

`letter` 			——> `[a-zA-Z]`

`specialinital` 	——> `! | $ | & | * | / | : | < | = | > | ? | ^ | _`

`subsequent`		——> `inital | number`

`number`			——> `digit digit*`

`digit` 			——> `[0-9]`

`boolean`			——> `#t|#f`

`string` 			——> `" stringelement* "`

`stringelement` 	——> `any other character except " and \\`

`comment` 		——> `; all subsquent characters up to line break`

`what?`


