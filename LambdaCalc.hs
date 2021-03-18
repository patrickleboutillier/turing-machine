module LambdaCalc where

import Prelude hiding (succ)

type Lambda a = (a -> a) -> a -> a

zero :: Lambda a
zero = \f x -> x

succ :: (Lambda a -> Lambda a)
succ = \p f x -> f $ p f x

one = succ zero 
two = succ one
three = succ two

plus :: (Lambda a) -> (Lambda a) -> (Lambda a)
plus = \p o f x -> (p f . o f) x

times :: (Lambda a) -> (Lambda a) -> (Lambda a)
times = \p o f x -> (p . o $ f) x

eval l = l (+1) 0