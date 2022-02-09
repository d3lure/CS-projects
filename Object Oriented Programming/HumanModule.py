from AnimalModule import Animal


class Human(Animal):
    def __init__(self, world, x, y, init=4, stren=5, age=0, cd=0, ct=0, ii=False):
        super(Human, self).__init__(world, x, y, 'H', init, stren, age)
        self.__cooldown = cd
        self.__is_immortal = ii
        self.__count_turns = ct

    def immortality(self):
        if self.__is_immortal is False and self.__cooldown <= 0:
            print("Super Ability Activated!")
            self.__is_immortal = True
            self.__count_turns = 0

    def action(self):
        x, y = self.get_position()

        if self.get_world().get_human_direction() == 'UP':
            y -= 1
        elif self.get_world().get_human_direction() == 'DOWN':
            y += 1
        elif self.get_world().get_human_direction() == 'RIGHT':
            x += 1
        elif self.get_world().get_human_direction() == 'LEFT':
            x -= 1

        if 0 <= x < self.get_world().get_width() and 0 <= y < self.get_world().get_height():
            empty = self.is_empty(x, y)
            if empty is True:
                self.set_position(x, y)
            elif self.__is_immortal is True and empty is not True:
                if empty.get_strength() > self.get_strength():
                    new_x, new_y = self.new_position()
                    self.set_position(new_x, new_y)
                else:
                    empty.collision(self)
            else:
                if empty.get_strength() > self.get_strength():
                    self.get_world().set_human(None)
                    self.get_world().set_human_direction(None)
                empty.collision(self)

        if self.__is_immortal is True:
            if self.__count_turns >= 5:
                self.__is_immortal = False
                self.__cooldown = 5
            self.__count_turns += 1
        elif self.__is_immortal is False and self.__cooldown > 0:
            self.__cooldown -= 1

    def collision(self, collider):
        if self.__is_immortal is False:
            super().collision(collider)

    def print_self(self):
        out = self.draw() + "%" + str(self.get_x()) \
              + "%" + str(self.get_y()) \
              + "%" + str(self.get_initiative()) \
              + "%" + str(self.get_strength()) \
              + "%" + str(self.get_age()) \
              + "%" + str(self.get_count_turns()) \
              + "%" + str(self.get_cooldown())  \
              + "%" + str(self.__is_immortal)
        return out

    def reproduce(self):
        pass

    def is_immortal(self):
        return self.__is_immortal

    def get_count_turns(self):
        return self.__count_turns

    def get_cooldown(self):
        return self.__cooldown

    def set_count_turns(self, cnt):
        self.__count_turns = cnt

    def set_cooldown(self, coold):
        self.__cooldown = coold


