import math
from SheepModule import Sheep


class CyberSheep(Sheep):
    def __init__(self, world, x, y, init=4, stren=11, age=0):
        super(Sheep, self).__init__(world, x, y, 'C', init, stren, age)
        self._kill_mode = False

    def action(self):
        self._kill_mode = False
        dist_x, dist_y = self.find_hogweed()
        x, y = self.get_position()

        if self._kill_mode is True:
            if x != dist_x:
                if x > dist_x:
                    x -= 1
                elif x < dist_x:
                    x += 1
            elif y != dist_y:
                if y > dist_y:
                    y -= 1
                elif y < dist_y:
                    y += 1

            empty = self.is_empty(x, y)
            if empty is True:
                self.set_position(x, y)
            else:
                empty.collision(self)
        else:
            super().action()

    def find_hogweed(self):
        from HogweedModule import Hogweed
        distance = math.sqrt(self.get_world().get_width() ** 2 + self.get_world().get_height() ** 2)
        dist_x, dist_y = 0, 0
        for org in self.get_world().get_organisms():
            if isinstance(org, Hogweed):
                self._kill_mode = True
                if self.calc_distance(org.get_x(), org.get_y()) < distance:
                    distance = self.calc_distance(org.get_x(), org.get_y())
                    dist_x, dist_y = org.get_x(), org.get_y()
        return dist_x, dist_y

    def calc_distance(self, dist_x, dist_y):
        dist = math.sqrt((dist_x - self.get_x()) ** 2 + (dist_y - self.get_y()) ** 2)
        return dist

    def reproduce(self):
        new_x, new_y = self.new_position()
        if new_x is not False:
            empty = self.is_empty(new_x, new_y)
            if empty is True:
                c = CyberSheep(self.get_world(), new_x, new_y)
                self.get_world().add_organism(c)
