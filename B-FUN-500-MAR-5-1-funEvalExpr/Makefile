NAME	= funEvalExpr

LOCAL_PATH = $(shell stack path --local-install-root)

EXEC_PATH	= $(LOCAL_PATH)/bin/EvalExpr-exe

RM	= rm -f

all:
	stack build
	cp $(EXEC_PATH) $(NAME)

clean:
	$(RM) funEvalExpr.cabal

fclean: clean
	$(RM) $(NAME)
	rm -rf .stack-work

re: fclean all