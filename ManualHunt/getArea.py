def request_handler(request):        
        values = request.get('values')
        arguments = request.get('args')
        index = 0
        xcord = -1
        ycord = -1
        while index < len(arguments):
            if arguments[index] == "x":
                xcord = index
            elif arguments[i] == "y":
                ycord = index
            index += 1
        if (xcord == -1 or ycord == -1):
            return 'You must enter an x and y value.'
        x_val = float(request['values']['x'])
        y_val = float(request['values']['y'])
        return get_area((x_val, y_val),locations)

def get_area(point_coord,locations):
    for place in locations:
        if within_area(point_coord, locations[place]):
            return place
    return "Outside MIT"


def within_area(point_coord,poly):
    num_crossed = 0
    x0, y0 = point_coord
    edges = []
    for i in range(-1, len(poly)-1): 
        x1, y1 = poly[i]
        x2, y2 = poly[i+1]
        edges.append(((x1 - x0, y1 - y0), (x2- x0, y2-y0)))
    
    
    edges_to_check = []
    for edge in edges: 
        if edge[0][1]*edge[1][1] <= 0: 
            edges_to_check.append(edge)
    #print(edges_to_check)
    for edge_ in edges_to_check: 
        x1 = edge_[0][0]
        x2 = edge_[1][0]
        y1 = edge_[0][1]
        y2 = edge_[1][1]
        if x1 > 0 and x2 > 0: 
            num_crossed +=1
        elif x1 <= 0 and x2 <= 0:
            continue
        elif x1*x2 <= 0: 
            p = (x1*y2 - y1*x2)/(y2-y1)
            if p >0: 
                num_crossed +=1
            else: 
                continue
        #print(num_crossed)
                    
    if num_crossed % 2 == 1: 
        return True
    else: 
        return False
    
def sign(x):
    if x > 0:
        return 1
    elif x == 0:
        return 0
    else:
        return -1
    
locations={
    "Student Center":[(-71.095863,42.357307),(-71.097730,42.359075),(-71.095102,42.360295),(-71.093900,42.359340),(-71.093289,42.358306)],
    "Dorm Row":[(-71.093117,42.358147),(-71.092559,42.357069),(-71.102987,42.353866),(-71.106292,42.353517)],
    "Simmons/Briggs":[(-71.097859,42.359035),(-71.095928,42.357243),(-71.106356,42.353580),(-71.108159,42.354468)],
    "Boston FSILG (West)":[(-71.124664,42.353342),(-71.125737,42.344906),(-71.092478,42.348014),(-71.092607,42.350266)],
    "Boston FSILG (East)":[(-71.092409,42.351392),(-71.090842,42.343589),(-71.080478,42.350900),(-71.081766,42.353771)],
    "Stata/North Court":[(-71.091636,42.361802),(-71.090950,42.360811),(-71.088353,42.361112),(-71.088267,42.362476),(-71.089769,42.362618)],
    "East Campus":[(-71.089426,42.358306),(-71.090885,42.360716),(-71.088310,42.361017),(-71.087130,42.359162)],
    "Vassar Academic Buildings":[(-71.094973,42.360359),(-71.091776,42.361770),(-71.090928,42.360636),(-71.094040,42.359574)],
    "Infinite Corridor/Killian":[(-71.093932,42.359542),(-71.092259,42.357180),(-71.089619,42.358274),(-71.090928,42.360541)],
    "Kendall Square":[(-71.088117,42.364188),(-71.088225,42.361112),(-71.082774,42.362032)],
    "Sloan/Media Lab":[(-71.088203,42.361017),(-71.087044,42.359178),(-71.080071,42.361619),(-71.082796,42.361905)],
    "North Campus":[(-71.11022,42.355325),(-71.101280,42.363934),(-71.089950,42.362666),(-71.108361,42.354484)],
    "Technology Square":[(-71.093610,42.363157),(-71.092130,42.365837),(-71.088182,42.364188),(-71.088267,42.362650)]
}
