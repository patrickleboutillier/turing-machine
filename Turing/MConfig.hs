module Turing.MConfig ((==>), asList, MCH(..), MConfig(MConfig), getDomain, Behaviour(..), 
  Turing.Base.Symbol, Turing.Base.blankSym, Turing.Base.matches, Turing.Base.Domain, Turing.Base.Operation(..)) where

import Turing.Base
import Data.Maybe
import Data.List


-- An MConfig is made up of 2 parts: the SymbolSpec and the Behaviour
data MConfig = MConfig String [(SymbolSpec, Behaviour)] | DynMConfig (Symbol -> MConfig)
instance Show MConfig where 
    show (MConfig name cbs) = init . concat $ map (\cb -> name ++ "\t-> " ++ showcb cb ++ "\n") cbs 
        where showcb (sspec, b) = (show sspec) ++ "\t-> " ++ (show b)
    show (DynMConfig f) = show $ f "*"
    showList (m:ms) = shows m . ("\n" ++) . showList ms
    showList [] = id

data Behaviour = Behaviour [Operation] MConfig
instance Show Behaviour where 
    show (Behaviour ops (MConfig name _)) = show ops ++ "\t-> " ++ name
    show (Behaviour ops dmc) = show ops ++ "\t-> " ++ show dmc

data MCH = Blank [Operation] MConfig | None [Operation] MConfig | Any [Operation] MConfig |
                 Sym Symbol [Operation] MConfig | Not Symbol [Operation] MConfig | 
                 OneOf [Symbol] [Operation] MConfig | NotOneOf [Symbol] [Operation] MConfig |
                 Var (Symbol -> MConfig)

(==>) :: String -> [MCH] -> MConfig
(==>) name mchs = MConfig name $ map cnv mchs
   where cnv (Turing.MConfig.Blank ops fmc) = (Turing.Base.Blank, Behaviour ops fmc)
         cnv (Turing.MConfig.None ops fmc) = (Turing.Base.None, Behaviour ops fmc)
         cnv (Turing.MConfig.Any ops fmc) = (Turing.Base.Any, Behaviour ops fmc)
         cnv (Turing.MConfig.Sym s ops fmc) = (Turing.Base.Sym s, Behaviour ops fmc)
         cnv (Turing.MConfig.Not s ops fmc) = (Turing.Base.Not s, Behaviour ops fmc)
         cnv (Turing.MConfig.OneOf ss ops fmc) = (Turing.Base.OneOf ss, Behaviour ops fmc)
         cnv (Turing.MConfig.NotOneOf ss ops fmc) = (Turing.Base.NotOneOf ss, Behaviour ops fmc)
         cnv (Turing.MConfig.Var f) = (Turing.Base.Blank, Behaviour [] (DynMConfig f))

traverseMConfig :: [(String, a)] -> (MConfig -> a) -> MConfig -> [(String, a)]
traverseMConfig seen f (DynMConfig df) = traverseMConfig seen f $ df blankSym
traverseMConfig seen f m@(MConfig name cbs) | isJust . lookup name $ seen = seen  
                                            | otherwise = foldl (\acc (sspec, Behaviour ops fmc) -> traverseMConfig acc f fmc) ((name, f m):seen) cbs

-- This will work as long as the unraveling m-functions does not make new symbols appear.
-- This is not the case with Turings m-functions.
getDomain :: MConfig -> Domain
getDomain = nub . sort . concat . concat . map snd . traverseMConfig [] f 
  where f (DynMConfig df) = []
        f (MConfig name cbs) = map (\(ss, Behaviour ops _) -> getSymbolSpecSymbols ss ++ getOpsSymbols ops) cbs

asList :: MConfig -> [MConfig]
asList = reverse . map snd . traverseMConfig [] id
