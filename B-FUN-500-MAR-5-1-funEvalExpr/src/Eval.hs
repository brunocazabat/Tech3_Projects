module Eval where

data Expr = Add Expr Expr
          | Sub Expr Expr
          | Mul Expr Expr
          | Div Expr Expr
          | Pow Expr Expr
          | Neg Expr
          | Num Double

eval :: Expr -> Double
eval e = case e of
    Add a b -> eval a + eval b
    Sub a b -> eval a - eval b
    Mul a b -> eval a * eval b
    Div a b -> eval a / eval b
    Neg a   -> eval a * (-1)
    Num n   -> n


