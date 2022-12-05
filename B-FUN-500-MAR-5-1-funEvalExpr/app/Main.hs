module Main where

import System.Environment
import Data.List
import Data.Maybe
import Data.Ord
import System.IO
import Debug.Trace
import System.Exit
import Data.Char
import Control.Exception
import Parser
import Eval



checkArgs :: [String] -> IO ()
checkArgs args = do
    if length args /= 1 then do
        putStrLn ("USAGE : ./funEvalExpr\tcalcul")
        exitWith (ExitFailure 84)
    else do
        return ()

main :: IO ()
main = do
    args <- getArgs
    checkArgs args

