NAME		= 	btc

CXX			= 	c++
CXXFLAGS	= 	-Wall -Wextra -Werror -std=c++98

SRCS		:= 	main.cpp\
				BitcoinExchange.cpp

HEADERS		:=	BitcoinExchange.hpp

OBJDIR		:= 	obj
OBJ 		:= 	$(SRCS:%.cpp=$(OBJDIR)/%.o)


# ---------------------------------------------------------------------------- #
#                                  BASE RULES                                  #
# ---------------------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(HEADERS) $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p '$(@D)'
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

# ---------------------------------------------------------------------------- #
#                                 FORMAT RULES                                 #
# ---------------------------------------------------------------------------- #
format:
	clang-format -style=file -i ${SRCS} ${HEADERS}

# ---------------------------------------------------------------------------- #
#                                 LINTER RULES                                 #
# ---------------------------------------------------------------------------- #
lint:
	clang-tidy ${HEADERS} -checks=-*,cppcoreguidelines-*,readability-*
	clang-tidy ${SRCS} -checks=-*,cppcoreguidelines-*,readability-*

# ------------------------------- END OF RULES ------------------------------- #

.PHONY: all clean fclean re format lint
