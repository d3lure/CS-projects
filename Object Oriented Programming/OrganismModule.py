from abc import ABC, abstractmethod
import random


class Organism(ABC):

    def __init__(self, world, x, y, sign='_', init=0, stren=0, age=0):
        self.__world = world
        self.__x = x
        self.__y = y
        self.__sign = sign
        self.__strength = stren
        self.__initiative = init
        self.__age = age

    def draw(self):
        return self.__sign

    def new_position(self):
        curr_x, curr_y = new_x, new_y = self.get_position()
        index = random.randint(0, 1)
        val = random.randint(0, 1)

        if index == 0:
            if val == 0:
                new_x += 1
            else:
                new_x -= 1
        else:
            if val == 0:
                new_y += 1
            else:
                new_y -= 1

        if 0 <= new_x < self.get_world().get_width() and 0 <= new_y < self.get_world().get_height():
            return new_x, new_y
        else:
            return False, False

    def set_position(self, new_x, new_y):
        from NullModule import Null
        self.get_board()[self.get_x()][self.get_y()] = Null()
        self.get_board()[new_x][new_y] = self
        self.__x = new_x
        self.__y = new_y

    def get_position(self):
        return self.__x, self.__y

    def is_empty(self, x, y):
        from NullModule import Null
        if type(self.get_board()[x][y]) != Null:
            return self.get_board()[x][y]
        else:
            return True

    def print_self(self):
        out = self.draw() + "%" + str(self.get_x()) + "%" + str(self.get_y()) \
               + "%" + str(self.get_initiative()) + "%" + str(self.get_strength()) \
               + "%" + str(self.get_age())
        return out

    def add_feed(self, o1, o2):
        log = ""
        log += o1.draw()
        log += " killed "
        log += o2.draw()
        log += " at "
        log += str(o2.get_position())
        self.get_world().set_feed(log)

    @abstractmethod
    def action(self):
        pass

    @abstractmethod
    def collision(self, collider):
        pass

    # GETTERS
    def get_board(self):
        return self.get_world().get_board()

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def get_world(self):
        return self.__world

    def get_age(self):
        return self.__age

    def get_strength(self):
        return self.__strength

    def get_initiative(self):
        return self.__initiative

    # SETTERS
    def set_age(self, age):
        self.__age = age

    def set_strength(self, strength):
        self.__strength = strength

    def set_initiative(self, initiative):
        self.__initiative = initiative

    def set_sign(self, sign):
        self.__sign = sign

    def set_world(self, world):
        self.__world = world



