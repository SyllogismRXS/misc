import sys

def str_2_gps_avg(coords_str):
    # Split by whitespace between coordinates, filter out empty results
    coords_str_list = filter(None, coords_str.split(' '))

    # Split lon/lat/alt by comma
    coords_list = [x.split(',') for x in coords_str_list]

    # convert all elements to float
    coords = [ (float(x), float(y), float(z)) for x,y,z in coords_list ]

    # Compute lat/lon/alt averages
    lon_avg = reduce(lambda x,y: x+y, [x for x,y,z in coords]) / len(coords)
    lat_avg = reduce(lambda x,y: x+y, [y for x,y,z in coords]) / len(coords)
    alt_avg = reduce(lambda x,y: x+y, [z for x,y,z in coords]) / len(coords)

    return (lon_avg, lat_avg, alt_avg)
    
def main():
    # Blue Base
    blue_base_str="-120.7702290233431,35.72229642711834,25 -120.7700250916915,35.72222313988945,25 -120.7697325625902,35.72230804603161,25 -120.7696295013943,35.72247669448272,25 -120.7697420047702,35.72271338647022,25 -120.7699470448227,35.72279053329226,25 -120.7702487886748,35.7227035048798,25 -120.7703412732398,35.7225376946166,25 -120.7702290233431,35.72229642711834,25 "
    lon, lat, alt = str_2_gps_avg(blue_base_str)    
    print('Blue Base Averages:')
    print('\tLon: %f' % lon)
    print('\tLat: %f' % lat)
    print('\tAlt: %f' % alt)

    # Gold Base
    gold_base_str="-120.7664129891356,35.721250710802,25 -120.7665112645653,35.72107983846779,25 -120.7663936445481,35.72083622666785,25 -120.7661941585179,35.72076335433645,25 -120.7659013868172,35.72085436236878,25 -120.7658007604123,35.72102142355285,25 -120.7659117453532,35.72125349541101,25 -120.7661130955043,35.72133492105527,25 -120.7664129891356,35.721250710802,25 "
    lon, lat, alt = str_2_gps_avg(gold_base_str)    
    print('Gold Base Averages:')
    print('\tLon: %f' % lon)
    print('\tLat: %f' % lat)
    print('\tAlt: %f' % alt)

if __name__ == '__main__':
    main()
    


