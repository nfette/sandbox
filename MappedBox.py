from numpy import exp, log
from scipy.special import expit, logit

class MappedVariable:
    
    def __init__(self,x_max,x_min):
        self.x_max = x_max
        self.x_min = x_min
    
    def x_to_y(self,x):
        # X in [min,max] is the raw variable; Y is the mapping to [-inf, inf].
        if self.x_min > -inf and self.x_max < inf:
            # Finite domain: use logit forward, expit back
            # First map to unit box
            y1 = (x - self.x_min) / (self.x_max - self.x_min)
            y = logit(y1)
        elif self.x_min > -inf:
            # Min only: use log forward, exp back
            y1 = (x - self.x_min)
            y = log(y1)
        elif self.x_max < inf:
            # Max only: use log forward, exp back
            y1 = (self.x_max - x)
            y = log(y1)
        else:
            y = x
        return y
    
    def y_to_x(self,y):
        if self.x_min > -inf and self.x_max < inf:
            # Finite domain: use logit forward, expit back
            y1 = expit(y)
            x = y1 * (self.x_max - self.x_min)+ self.x_min
        elif self.x_min > -inf:
            # Min only: use log forward, exp back
            y1 = exp(y)
            x = y1 + self.x_min
        elif self.x_max < inf:
            # Max only: use log forward, exp back
            y1 = exp(y)
            x = self.x_max - y1
        else:
            x = y
        return x

class MappedBox:
    def __init__(self, min_max_pairs):
        lars = []
        for x_min,x_max in min_max_pairs:
            lars.append(MappedVariable(x_min, x_max))
    def x_to_y(self,x):
        pass
    def y_to_x(self,y):
        pass
    
box_ptw = MappedBox([(0,inf),(0,inf),(0,10)])
