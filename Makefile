##
## EPITECH PROJECT, 2024
## bsraytracer
## File description:
## Makefile
##

NAME	=	raytracer

CC		=	g++ -g3
RM		=	rm -rf

CORE_SRC				= $(shell find src -type f -name "*.cpp")
POINTLIGHT_SRC 			= $(shell find src/lights/pointLight -type f -name "*.cpp")
DIRECTIONALLIGHT_SRC	= $(shell find src/lights/directionalLight -type f -name "*.cpp")
SPHERE_SRC 				= $(shell find src/primitives/sphere -type f -name "*.cpp")
PLANE_SRC 				= $(shell find src/primitives/plane -type f -name "*.cpp")
CYLINDER_SRC 			= $(shell find src/primitives/cylinder -type f -name "*.cpp")
CONE_SRC 				= $(shell find src/primitives/cone -type f -name "*.cpp")

CORE_OBJ				= $(CORE_SRC:.cpp=.o)
POINTLIGHT_OBJ 			= $(POINTLIGHT_SRC:.cpp=.o)
DIRECTIONALLIGHT_OBJ	= $(DIRECTIONALLIGHT_SRC:.cpp=.o)
SPHERE_OBJ 				= $(SPHERE_SRC:.cpp=.o)
PLANE_OBJ 				= $(PLANE_SRC:.cpp=.o)
CYLINDER_OBJ 			= $(CYLINDER_SRC:.cpp=.o)
CONE_OBJ 				= $(CONE_SRC:.cpp=.o)

FLAGS	= 	-std=c++20 -Wall -Wextra -Werror

$(NAME):	core lights primitives

core:	$(CORE_OBJ)
	@$(CC) -o $(NAME) $(CORE_OBJ) -fno-gnu-unique -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system

lights:	$(POINTLIGHT_OBJ) $(DIRECTIONALLIGHT_OBJ)
	@$(CC) -shared -fPIC -o plugins/point_light.so $(POINTLIGHT_OBJ)
	@$(CC) -shared -fPIC -o plugins/directional_light.so $(DIRECTIONALLIGHT_OBJ)

primitives:	$(SPHERE_OBJ) $(PLANE_OBJ) $(CYLINDER_OBJ) $(CONE_OBJ)
	@$(CC) -shared -fPIC -o plugins/sphere.so $(SPHERE_OBJ)
	@$(CC) -shared -fPIC -o plugins/plane.so $(PLANE_OBJ)
	@$(CC) -shared -fPIC -o plugins/cylinder.so $(CYLINDER_OBJ)
	@$(CC) -shared -fPIC -o plugins/cone.so $(CONE_OBJ)

%.o: %.cpp
	@$(CC) -c $< -o $@ -fPIC $(FLAGS)

all:	$(NAME)

clean:
	@$(RM) $(CORE_OBJ) $(POINTLIGHT_OBJ) $(DIRECTIONALLIGHT_OBJ) $(SPHERE_OBJ) $(PLANE_OBJ) $(CYLINDER_OBJ) $(CONE_OBJ) $(LIGHTS_OBJ) $(PRIMITIVES_OBJ)
	@find . -name "*~" -delete -o -name "#*#" -delete
	@$(RM) vgcore.*
	@$(RM) a.out
	@find . -name "*.gc*" -delete

fclean:	clean
	@$(RM) $(NAME) plugins/*.so

re:		fclean all
