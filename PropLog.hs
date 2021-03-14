module PropLog where

import Prelude hiding ((&))
import Data.List
import Data.Maybe
import Control.Spoon

-- See page 204 of TAT




findN :: ([Bool] -> a) -> Int
findN f = fst . head . dropWhile (isNothing . snd) . map (\ts -> (length ts, teaspoon $ f ts)) . inits $ true
    where true = True:true

cartProdn :: [a] -> Int -> [[a]]
cartProdn ls 0 = []
cartProdn ls 1 = map (\l -> [l]) ls
cartProdn ls 2 = [[x, y] | x <- ls, y <- ls]
cartProdn ls n = [x : t | x <- ls, t <- cartProdn ls (n - 1)]

genTT :: ([Bool] -> Bool) -> [([Bool], Bool)]
genTT fa = map (\i -> (i, fa i)) input
    where input = cartProdn [True, False] $ findN fa

-- Returns True id the 2 passed propositions are equivalent, i.e. have the same truth table.
eq :: ([Bool] -> Bool) -> ([Bool] -> Bool) -> Bool
eq fa fb | findN fa /= findN fb = undefined
         | otherwise = genTT fa == genTT fb 

--    where cartProd ls 2 = [[x, y] | x <- ls, y <- ls]
--          cartProd ls n = [x : t | x <- ls, t <- cartProdn ls (n - 1)]


-- A few definitions
v = (||)
(&) = (&&)
t = True
f = False

implies False False = True
implies False True  = True
implies True  False = False
implies True  True  = True
(-->) = implies

iif False False = True
iif False True  = False
iif True  False = False
iif True  True  = True
(~) = iif

tautology :: ([Bool] -> Bool) -> Bool
tautology = all (== True). map (\(i, o) -> o) . genTT 

contradiction :: ([Bool] -> Bool) -> Bool
contradiction = all (== False). map (\(i, o) -> o) . genTT 

satisfiable :: ([Bool] -> Bool) -> Bool
satisfiable = any (== True). map (\(i, o) -> o) . genTT 

qualify :: ([Bool] -> Bool) -> String
qualify f | tautology f = "valid"
qualify f | contradiction f = "contradiction"
qualify f | otherwise = "safisfiable"


main = do
    print $ (\[x] -> x `v` x) `eq` (\[x] -> x)
    print $ (\[x] -> x & x) `eq` (\[x] -> x)
    print $ (\[x] -> x `v` t) `eq` (\[x] -> t)
    print $ (\[x] -> x `v` f) `eq` (\[x] -> x)
    print $ (\[x] -> x & t) `eq` (\[x] -> x)
    print $ (\[x] -> x & f) `eq` (\[x] -> f)
    print $ (\[x, y] -> x `v` y) `eq` (\[x, y] -> y `v` x)
    print $ (\[x, y] -> x & y) `eq` (\[x, y] -> y & x)

    -- page 207
    print $ (\[x] -> x `v` not x) `eq` (\[x] -> t)
    print $ (\[x] -> x & not x) `eq` (\[x] -> f)

    print $ (\[x,y] -> not $ x `v` y) `eq` (\[x,y] -> not x & not y)  
    print $ (\[x,y] -> not $ x & y) `eq` (\[x,y] -> not x `v` not y)  

    print $ (\[x,y] -> x `v` y) `eq` (\[x,y] -> not $ not x & not y)  
    print $ (\[x,y] -> x & y) `eq` (\[x,y] -> not $ not x `v` not y)  

    -- page 208
    print $ (\[x,y,z] -> x & not y `v` z) `eq` (\[x,y,z] -> not $ not x `v` y & not z)   

    -- page 209
    print $ (\[x,y] -> x --> y) `eq` (\[x,y] -> not y --> not x)
    print $ (\[x,y] -> x --> y) `eq` (\[x,y] -> not x `v` y)
    print $ (\[x,y] -> x --> y) `eq` (\[x,y] -> not $ x & not y)

    print $ (\[x,y] -> (x & y) --> x) `eq` (\[x,y] -> (x & y) --> y)

    print $ (\[x,y] -> x ~ y) `eq` (\[x,y] -> (x --> y) & (y --> x))

    -- page 210
    let t = (\[x,y] -> x `v` y `v` (not x & not y))
    print $ tautology t
    let c = (\[x,y] -> x & y & not x)
    print $ contradiction c
    let s = (\[x,y] -> x `v` (y & not y))
    print $ map satisfiable [s, t]
    print $ map qualify [t, c, s]