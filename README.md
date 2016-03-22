# myscheme
A Scheme Interpreter Using C++

###词法规则：

`token` 		——> `identifer` | `number` | `boolean` | `string` | `(` | `)` | `.`

`identifer`		——> `inital` `subsequent*` | `peculiaridentifer`

`delimiter`		——> `space` | `newline` | `(` | `)` | `"` | `;`

`peculiaridentifer`	——> `+` | `-`

`inital` 		——> `letter` | `specialinital`

`letter` 		——> `[a-zA-Z]`

`specialinital` 	——> `!` | `$` | `&` | `*` | `/` | `:` | `<` | `=` | `>` | `?` | `^` | `_`

`subsequent`		——> `inital` | `digit` | `specialsubsequent`

`specialsubsequent`	——> `+` | `-` | `.`

`number`		——> `[sign]` `digit` `digit*`

`sign`			——> `+` | `-`

`digit` 		——> `[0-9]`

`boolean`		——> `#t`|`#f`

`string` 		——> `" stringelement* "`

`stringelement` 	——> `any other character except " and \\`

`comment` 		——> `; all subsquent characters up to line break`

`keyword`   		——> `quote` | `lambda` | `if` | `set!` | `begin` | `cond` | `and` | `or` | `case` | `let` | `delay`


###文法规则：
`expression` 		——> `variable`
	| `literal`
	| `procedure call`
	| `lambda expression`
	| `conditional`
	| `assignment`

`literal` 		——> `self-evaluating` | `quotation`

`self-evaluating`	——> `number` | `boolean` | `string`

`procedure call`	——> `(operator operand*)`

`operator`		——> `expression`

`operand`		——> `expression`

`lambda expression`     ——> `(lambda formals body)`

`formals`		——> `(variable*)` | `variable` | `(variable+ . variable)`

`body`			——> `definition*` `sequence`

`sequence`		——> `command*` `expression`

`conditional`		——> `(if test consqeuence alternate)`

`test`			——> `expression`

`consqeuence`		——> `expression`

`alternate`		——> `expression` | `empty`
