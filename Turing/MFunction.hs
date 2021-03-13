{-# LANGUAGE TypeSynonymInstances #-}
{-# LANGUAGE FlexibleInstances #-}

module Turing.MFunction ((%)) where

import Turing.Base (Symbol)
import Turing.MConfig
 

class Named a where
    name :: a -> String

instance Named Symbol where 
    name s = "'" ++ s ++ "'"
instance Named MConfig where 
    name (MConfig n _) = n

instance (Named a, Named b) => Named (a, b) where
    name (a, b) = "(" ++ name a ++ "," ++ name b ++ ")"
instance (Named a, Named b, Named c) => Named (a, b, c) where
    name (a, b, c) = "(" ++ name a ++ "," ++ name b ++ "," ++ name c ++ ")"
instance (Named a, Named b, Named c, Named d) => Named (a, b, c, d) where
    name (a, b, c, d) = "(" ++ name a ++ "," ++ name b ++ "," ++ name c ++ "," ++ name d ++")"
instance (Named a, Named b, Named c, Named d, Named e) => Named (a, b, c, d, e) where
    name (a, b, c, d, e) = "(" ++ name a ++ "," ++ name b ++ "," ++ name c ++ "," ++ name d ++ "," ++ name e ++ ")"
instance (Named a, Named b, Named c, Named d, Named e, Named f) => Named (a, b, c, d, e, f) where
    name (a, b, c, d, e, f) = "(" ++ name a ++ "," ++ name b ++ "," ++ name c ++ "," ++ name d ++ "," ++ name e ++ "," ++ name f ++ ")"


(%) :: (Named a) => String -> a -> String
(%) f x = f ++ pp
    where n  = name x
          pp | head n == '(' = n
             | otherwise = "(" ++ n ++ ")"