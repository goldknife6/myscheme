# myscheme
A Scheme Interpreter Using C++

词法：

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
