import os
import pygame
import tkinter as tk
from tkinter import *
import tkinter.filedialog
from tkinter.filedialog import asksaveasfile
from random import randrange
from NullModule import Null
from WolfModule import Wolf
from GrassModule import Grass
from SheepModule import Sheep
from DandelionModule import Dandelion
from TurtleModule import Turtle
from FoxModule import Fox
from GuaranaModule import Guarana
from HogweedModule import Hogweed
from WildBerriesModule import WildBerries
from AntelopeModule import Antelope
from HumanModule import Human
from CyberSheepModule import CyberSheep


class World:

    def __init__(self, x=0, y=0, win=None):
        self.__width = x
        self.__height = y
        self.__round = 0
        self.__organisms = []
        self.__feed = ""
        if x != 0:
            self.__board = [[Null() for i in range(self.__height)] for j in range(self.__width)]
            self.square_size = win.get_width() // self.__width

        self.__human_direction = None
        self.__human = None
        self._window = win
        self.log_win = None

    def sort_organisms(self):
        # self.__organisms.sort(key=lambda o: o.get_age(), reverse=True)
        self.__organisms.sort(key=lambda o: o.get_initiative(), reverse=True)

    def make_turn(self):
        self.__feed = ""
        self.sort_organisms()
        tmp = self.__organisms

        for o in tmp:
            o.action()
            o.set_age(o.get_age() + 1)

        self.__round += 1
        self.print_world()
        print(self.__feed)

    def game_feed(self, log):
        self.__feed += log

    def make_ground(self):
        for y in range(self.__height):
            for x in range(self.__width):
                dirt = pygame.image.load(os.path.join('profiles', 'null.png'))
                dirt = pygame.transform.scale(dirt, (self.square_size, self.square_size))
                self._window.blit(dirt, (x * self.square_size, y * self.square_size))

    def print_world(self):
        self.make_ground()
        out = ""
        for y in range(self.__height):
            for x in range(self.__width):
                org = self.__board[x][y]
                img = self.choose_image(org)
                self._window.blit(img, (x * self.square_size, y * self.square_size))
                out += self.__board[x][y].draw()
            out += '\n'
        out += f"\nRound: {self.__round} | " + self.get_state_of_ability()
        print(out)

    def get_state_of_ability(self):
        if self.__human:
            if self.get_human().is_immortal() is True:
                log = "Immortality round: "
                log += str(self.get_human().get_count_turns())
                return log
            else:
                log = "Rounds left to ability: "
                log += str(self.get_human().get_cooldown())
                return log
        else:
            return "Human is dead"

    def add_organism(self, organism):
        self.get_organisms().append(organism)
        self.__board[organism.get_x()][organism.get_y()] = organism

    def kill_organism(self, organism):
        self.get_organisms().remove(organism)
        x, y = organism.get_x(), organism.get_y()
        self.__board[x][y] = Null()

    def random_world_generator(self, n):
        rand_x, rand_y = randrange(self.__width), randrange(self.__height)
        h = Human(self, rand_x, rand_y)
        self.add_organism(h)
        self.__human = h

        for i in range(n):
            x = randrange(self.__width)
            y = randrange(self.__height)

            if isinstance(self.__board[x][y], Null):
                tmp = randrange(11)
                if tmp == 0:
                    self.add_organism(Wolf(self, x, y))
                elif tmp == 1:
                    self.add_organism(Sheep(self, x, y))
                elif tmp == 2:
                    self.add_organism(Grass(self, x, y))
                elif tmp == 3:
                    self.add_organism(Dandelion(self, x, y))
                elif tmp == 4:
                    self.add_organism(Turtle(self, x, y))
                elif tmp == 5:
                    self.add_organism(Guarana(self, x, y))
                elif tmp == 6:
                    self.add_organism(WildBerries(self, x, y))
                elif tmp == 7:
                    self.add_organism(Fox(self, x, y))
                elif tmp == 8:
                    self.add_organism(Antelope(self, x, y))
                elif tmp == 9:
                    self.add_organism(Hogweed(self, x, y))
                elif tmp == 10:
                    self.add_organism(CyberSheep(self, x, y))

        self.print_world()

    def save_to_file(self, name):
        file = open(name, "w")
        file.write(str(self.__width) + "%" + str(self.__height) + "%" + str(self.__round) \
                   + "%" + str(len(self.__organisms)) + '\n')
        for o in self.__organisms:
            file.write(o.print_self() + '\n')
        file.close()

    def load_from_file(self, name):
        if os.path.isfile(name):

            file = open(name, "r")
            self.__feed = ""
            self.__board = []
            self.__organisms = []
            data = file.readline()
            data = data.split('%')
            self.__width = int(data[0])
            self.__height = int(data[1])
            self.__round = int(data[2])
            self.__board = [[Null() for i in range(self.__height)] for j in range(self.__width)]

            for i in range(int(data[3])):
                data = file.readline()
                data = data.split('%')
                print(data)
                org = data[0]
                x = int(data[1])
                y = int(data[2])
                init = int(data[3])
                stren = int(data[4])
                age = int(data[5])

                if org == 'A':
                    self.add_organism(Antelope(self, x, y, init, stren, age))
                elif org == 'C':
                    self.add_organism(CyberSheep(self, x, y, init, stren, age))
                elif org == 'F':
                    self.add_organism(Fox(self, x, y, init, stren, age))
                elif org == 'H':
                    if data[8] == "False\n":
                        boolean = False
                    else:
                        boolean = True

                    h = Human(self, x, y, init, stren, age, int(data[7]), int(data[6]), boolean)
                    self.add_organism(h)
                    self.__human = h
                elif org == 'S':
                    self.add_organism(Sheep(self, x, y, init, stren, age))
                elif org == 'T':
                    self.add_organism(Turtle(self, x, y, init, stren, age))
                elif org == 'W':
                    self.add_organism(Wolf(self, x, y, init, stren, age))
                elif org == '+':
                    self.add_organism(Guarana(self, x, y, stren, age))
                elif org == '!':
                    self.add_organism(Hogweed(self, x, y, stren, age))
                elif org == ':':
                    self.add_organism(WildBerries(self, x, y, stren, age))
                elif org == '*':
                    self.add_organism(Dandelion(self, x, y, stren, age))
                elif org == '"':
                    self.add_organism(Grass(self, x, y, stren, age))

            self.print_world()
            file.close()
        else:
            print("File doesnt exist!")

    def choose_image(self, org):
        img = None

        if type(org) == Null:
            img = pygame.image.load(os.path.join('profiles', 'null.png'))
        elif type(org) == Human:
            if org.is_immortal() is True:
                img = pygame.image.load(os.path.join('profiles', 'human_immortal.png'))
            else:
                img = pygame.image.load(os.path.join('profiles', 'human.png'))
        elif type(org) == WildBerries:
            img = pygame.image.load(os.path.join('profiles', 'wild_berries.png'))
        elif type(org) == Dandelion:
            img = pygame.image.load(os.path.join('profiles', 'dandelion.png'))
        elif type(org) == Sheep:
            img = pygame.image.load(os.path.join('profiles', 'sheep.png'))
        elif type(org) == Wolf:
            img = pygame.image.load(os.path.join('profiles', 'wolf.png'))
        elif type(org) == Guarana:
            img = pygame.image.load(os.path.join('profiles', 'guarana.png'))
        elif type(org) == Grass:
            img = pygame.image.load(os.path.join('profiles', 'grass.png'))
        elif type(org) == CyberSheep:
            img = pygame.image.load(os.path.join('profiles', 'cyber_sheep.png'))
        elif type(org) == Hogweed:
            img = pygame.image.load(os.path.join('profiles', 'hogweed.png'))
        elif type(org) == Turtle:
            img = pygame.image.load(os.path.join('profiles', 'turtle.png'))
        elif type(org) == Fox:
            img = pygame.image.load(os.path.join('profiles', 'fox.png'))
        elif type(org) == Antelope:
            img = pygame.image.load(os.path.join('profiles', 'antelope.png'))

        img = pygame.transform.scale(img, (self.square_size, self.square_size))
        return img

    def prompt_file(self):
        top = tk.Tk()
        top.withdraw()
        file_name = tk.filedialog.askopenfilename(parent=top)
        top.destroy()
        return file_name

    def prompt_save_file(self):
        top = tk.Tk()
        top.withdraw()
        file_name = tk.filedialog.asksaveasfilename(parent=top)
        top.destroy()
        return file_name

    def add_org_window(self, x, y):

        if type(self.__board[x][y]) == Null:

            def add(org):
                self.add_organism(org)
                win.quit()
                win.withdraw()

            win = tk.Tk()
            frame = tk.Frame(win)
            frame.pack()

            Button(win, text="Add Wolf", command=lambda: add(Wolf(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Sheep", command=lambda: add(Sheep(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Antelope", command=lambda: add(Antelope(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Turtle", command=lambda: add(Turtle(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Fox", command=lambda: add(Fox(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add CyberSheep", command=lambda: add(CyberSheep(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Grass", command=lambda: add(Grass(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Guarana", command=lambda: add(Guarana(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Dandelion", command=lambda: add(Dandelion(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add WildBerries", command=lambda: add(WildBerries(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)
            Button(win, text="Add Hogweed", command=lambda: add(Hogweed(self, x, y)), fg="black",
                   bg="white", width=20).pack(pady=0)

            Button(win, text="Quit", command=quit, fg="white",
                   bg="red", width=20).pack(pady=10)

            win.mainloop()

    def get_pos_mouse(self, pos):
        x, y = pos
        row = x // self.square_size
        col = y // self.square_size
        return row, col

    # SETTERS
    def set_human_direction(self, direction):
        self.__human_direction = direction

    def set_height(self, x):
        self.__width = x

    def set_width(self, y):
        self.__height = y

    def set_human(self, h):
        self.__human = h

    def set_feed(self, log):
        self.__feed += log
        self.__feed += '\n'

    # GETTERS
    def get_board(self):
        return self.__board

    def get_round(self):
        return self.__round

    def get_height(self):
        return self.__height

    def get_width(self):
        return self.__width

    def get_organisms(self):
        return self.__organisms

    def get_organism(self, index):
        return self.__organisms[index]

    def get_human(self):
        return self.__human

    def get_human_direction(self):
        return self.__human_direction

    def get_num_organisms(self):
        return len(self.__organisms)

    def get_feed(self):
        return self.__feed
