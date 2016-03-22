# myscheme
A Scheme Interpreter Using C++

###词法规则：

`Token` 		——> `Identifer` | `Number` | `Boolean` | `String` | `(` | `)` | `.`

`Identifer`		——> `Inital` `Subsequent*` | `PeculiarIdentifer`

`Delimiter`		——> `Space` | `Newline` | `(` | `)` | `"` | `;`

`PeculiarIdentifer`	——> `+` | `-`

`Inital` 		——> `Letter` | `SpecialInital`

`Letter` 		——> `[a-zA-Z]`

`SpecialInital` 	——> `!` | `$` | `&` | `*` | `/` | `:` | `<` | `=` | `>` | `?` | `^` | `_`

`Subsequent`		——> `Inital` | `Digit` | `SpecialSubsequent`

`SpecialSubsequent`	——> `+` | `-` | `.`

`Number`		——> `[Sign]` `Digit` `Digit*`

`Sign`			——> `+` | `-`

`Digit` 		——> `[0-9]`

`Boolean`		——> `#t`|`#f`

`String` 		——> `" StringElement* "`

`StringElement` 	——> `any other character except " and \\`

`Comment` 		——> `; all subsquent characters up to line break`

`keyword`   		——> `quote` | `lambda` | `if` | `set!` | `begin` | `cond` | `and` | `or` | `case` | `let` | `delay`


###文法规则：
`Expression` 		——> `Variable`
        <br>>	| `Literal`
        <br>	| `ProcedureCall`
        <br>	| `LambdaExpression`
        <br>	| `Conditional`
        <br>	| `Assignment`

`Literal` 		——> `Self-evaluating` | `Quotation`

`Self-evaluating`	——> `Number` | `Boolean` | `String`

`ProcedureCall`		——> `(Operator Operand*)`

`Operator`		——> `Expression`

`Operand`		——> `Expression`

`LambdaExpression`     ——> `(lambda Formals Body)`

`Formals`		——> `(Variable*)` | `Variable` | `(Variable+ . Variable)`

`Body`			——> `Definition*` `Sequence`

`Sequence`		——> `Command*` `Expression`

`Command`		——> `Expression`

`Conditional`		——> `(if Test Consqeuence Alternate)`

`Test`			——> `Expression`

`Consqeuence`		——> `Expression`

`Alternate`		——> `Expression` | `Empty`

`Program`		——> `CommandOrDefinition*`

`CommandOrDefinition`   ——> `Command`

	| `Definition`

	| `(begin CommandOrDefinition+)`

`Definition`		——> `(define Variable Expression)`

	| `(define (Variable DefFormals) Body)`

`DefFormals` 		——> `Variable*`

	| `Variable* . Variable`
