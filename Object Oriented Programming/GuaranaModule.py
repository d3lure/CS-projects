from PlantModule import Plant
from NullModule import Null


class Guarana(Plant):
    def __init__(self, world, x, y, stren=0, age=0):
        super(Guarana, self).__init__(world, x, y, '+', stren, age)

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            if type(self.get_board()[new_x][new_y]) == Null:
                g = Guarana(self.get_world(), new_x, new_y)
                self.get_world().add_organism(g)

    def collision(self, collider):
        collider.set_strength(collider.get_strength() + 3)
        log = ""
        log += collider.draw()
        log += " has eaten +, its strength is now: "
        log += str(collider.get_strength())
        self.get_world().set_feed(log)
        super().collision(collider)