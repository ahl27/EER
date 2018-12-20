import argparse
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
import os
import numpy as np
from statistics import stdev
from operator import add

plt.style.use('seaborn-darkgrid')
cwd = os.getcwd()
plot_market = True

def weird_zip(arr1, arr2):
    for i in range(len(arr1)):
        arr1[i].append(arr2[i])

def read_from_file(data):
    newline = data.split('\n')[2:-1]
    specs = [float(x.split()[3]) for x in newline]
    pop = [float(x.split()[4]) for x in newline]
    totals = [float(x.split()[1]) + float(x.split()[2]) for x in newline]
    red = [(float(x.split()[1])) / (float(x.split()[1]) + float(x.split()[2])) 
        if (float(x.split()[1]) + float(x.split()[2])) != 0 else 0.5
        for x in newline]
    green = [(float(x.split()[2])) / (float(x.split()[1]) + float(x.split()[2])) 
        if (float(x.split()[1]) + float(x.split()[2])) != 0 else 0.5
        for x in newline]

    return [specs, pop, totals, red, green]

def plot_vals(plot, data, ylim=None, title=None, top=False):
    if not top:
        loc = 'lower right'
    else:
        loc = 'upper right'
    for datum in data:
        plot.plot(datum)
    if plot_market:
        legend = ['no spec, best', 'spec, best', 'no spec, market', 'spec, market']
    else:
        legend = ['no specialization', 'specialization']
    plot.legend(legend, loc=loc)
    if ylim is not None:
        plot.set_ylim(ylim)
    if title is not None:
        plot.set_title(title)

def plot_totals(keyval):
    NUM_RUNS = 20
    filepath = cwd + '/' + keyval + 'Pucks/pucks_vanilla' + keyval
    plot_market_fp = cwd + '/' + keyval + 'mktPucks/pucks_vanilla' + keyval + 'market'
    spec1_complete = [[] for i in range(101)]
    #green_complete = [[] for i in range(101)]

    for i in range(NUM_RUNS):
        data1 = open( filepath + 'nospec_' + str(i) + '.txt').read()
        data2 = open( filepath + '_' + str(i) + '.txt').read()

        ret1 = read_from_file(data1)
        ret2 = read_from_file(data2)


        if plot_market:
            data3 = open( plot_market_fp + 'nospec_' + str(i) + '.txt').read()
            data4 = open( plot_market_fp + '_' + str(i) + '.txt').read()            

            ret3 = read_from_file(data3)
            ret4 = read_from_file(data4)

        if i == 0:
            #ret_list = [specs, pop, totals, red, green]
            spec_list1 = ret1[0]
            spec_list2 = ret2[0]
            pop_list1 = ret1[1]
            pop_list2 = ret2[1]
            totals_list1 = ret1[2]
            totals_list2 = ret2[2]

            avgpp1_full = [[totals_list1[x] / pop_list1[x]] for x in range(len(totals_list1))]
            avgpp2_full = [[totals_list2[x] / pop_list2[x]] for x in range(len(totals_list2))]

            red_list1 = ret1[3]
            red_list2 = ret2[3]
            green_list1 = ret1[4]
            green_list2 = ret2[4]

            spec_test = [[x] for x in spec_list1]
            # avgpp1 = pucksper1
            # avgpp2 = pucksper2

            if plot_market:
                spec_list3 = ret3[0]
                spec_list4 = ret4[0]
                pop_list3 = ret3[1]
                pop_list4 = ret4[1]
                totals_list3 = ret3[2]
                totals_list4 = ret4[2]
                avgpp3_full = [[totals_list3[x] / pop_list3[x]] for x in range(len(totals_list3))]
                avgpp4_full = [[totals_list4[x] / pop_list4[x]] for x in range(len(totals_list4))]
                red_list3 = ret3[3]
                red_list4 = ret4[3]
                green_list3 = ret3[4]
                green_list4 = ret4[4]
                # avgpp3 = pucksper3
                # avgpp4 = pucksper4


        else:
            #this can definitely be shortened somehow
            spec_list1 = [sum(x) for x in zip(spec_list1, ret1[0])]
            spec_list2 = [sum(x) for x in zip(spec_list2, ret2[0])]
            pop_list1 = [sum(x) for x in zip(pop_list1, ret1[1])]
            pop_list2 = [sum(x) for x in zip(pop_list2, ret2[1])]
            totals_list1 = [sum(x) for x in zip(totals_list1, ret1[2])]
            totals_list2 = [sum(x) for x in zip(totals_list2, ret2[2])]
            avgpp1 = [totals_list1[x] / pop_list1[x] for x in range(len(totals_list1))]
            avgpp2 = [totals_list2[x] / pop_list2[x] for x in range(len(totals_list2))]
            
            red_list1 = [sum(x) for x in zip(red_list1, ret1[3])]
            red_list2 = [sum(x) for x in zip(red_list2, ret2[3])]
            green_list1 = [sum(x) for x in zip(green_list1, ret1[4])]
            green_list2 = [sum(x) for x in zip(green_list2, ret2[4])]

            weird_zip(avgpp1_full, avgpp1)
            weird_zip(avgpp2_full, avgpp2)

            if plot_market:
                spec_list3 = [sum(x) for x in zip(spec_list3, ret3[0])]
                spec_list4 = [sum(x) for x in zip(spec_list4, ret4[0])]
                pop_list3 = [sum(x) for x in zip(pop_list3, ret3[1])]
                pop_list4 = [sum(x) for x in zip(pop_list4, ret4[1])]
                totals_list3 = [sum(x) for x in zip(totals_list3, ret3[2])]
                totals_list4 = [sum(x) for x in zip(totals_list4, ret4[2])]
                avgpp3 = [totals_list3[x] / pop_list3[x] for x in range(len(totals_list3))]
                avgpp4 = [totals_list4[x] / pop_list4[x] for x in range(len(totals_list4))]
                weird_zip(avgpp3_full, avgpp3)
                weird_zip(avgpp4_full, avgpp4)
                
                red_list3 = [sum(x) for x in zip(red_list3, ret3[3])]
                red_list4 = [sum(x) for x in zip(red_list4, ret4[3])]
                green_list3 = [sum(x) for x in zip(green_list3, ret3[4])]
                green_list4 = [sum(x) for x in zip(green_list4, ret4[4])]

    spec_list1 = [x/NUM_RUNS for x in spec_list1]
    spec_list2 = [x/NUM_RUNS for x in spec_list2]
    pop_list1 = [x/NUM_RUNS for x in pop_list1]
    pop_list2 = [x/NUM_RUNS for x in pop_list2]
    totals_list1 = [x/NUM_RUNS for x in totals_list1]
    totals_list2 = [x/NUM_RUNS for x in totals_list2]
    avgpp1 = [x/NUM_RUNS for x in avgpp1]
    avgpp2 = [x/NUM_RUNS for x in avgpp2]

    red_list1 = [x/NUM_RUNS for x in red_list1]
    red_list2 = [x/NUM_RUNS for x in red_list2]
    green_list1 = [x/NUM_RUNS for x in green_list1]
    green_list2 = [x/NUM_RUNS for x in green_list2]

    if plot_market:
        spec_list3 = [x/NUM_RUNS for x in spec_list3]
        spec_list4 = [x/NUM_RUNS for x in spec_list4]
        pop_list3 = [x/NUM_RUNS for x in pop_list3]
        pop_list4 = [x/NUM_RUNS for x in pop_list4]
        totals_list3 = [x/NUM_RUNS for x in totals_list3]
        totals_list4 = [x/NUM_RUNS for x in totals_list4]
        avgpp3 = [x/NUM_RUNS for x in avgpp3]
        avgpp4 = [x/NUM_RUNS for x in avgpp4]
        red_list3 = [x/NUM_RUNS for x in red_list3]
        red_list4 = [x/NUM_RUNS for x in red_list4]
        green_list3 = [x/NUM_RUNS for x in green_list3]
        green_list4 = [x/NUM_RUNS for x in green_list4]

    pp1_dev = [stdev(avgpp1_full[i]) for i in range(len(avgpp1_full))]
    pp2_dev = [stdev(avgpp2_full[i]) for i in range(len(avgpp2_full))]
    pp3_dev = [stdev(avgpp3_full[i]) for i in range(len(avgpp3_full))]
    pp4_dev = [stdev(avgpp4_full[i]) for i in range(len(avgpp4_full))]       

    plt.figure(figsize=(16,8))
    spec_plot = plt.subplot(231)
    pop_plot = plt.subplot(232)
    totals_plot = plt.subplot(233)
    avgpp_plot = plt.subplot(234)
    red_plot = plt.subplot(235)
    #green_plot = plt.subplot(246)
    test_plot = plt.subplot(236)

    #plot_vals(plot, data, ylim=None, legend=None, title=None)
    specs = [spec_list1, spec_list2]
    if plot_market:
        specs.append(spec_list3)
        specs.append(spec_list4)       
    plot_vals(spec_plot, specs, [0,1], "Specialization")

    pops = [pop_list1, pop_list2]
    if plot_market:
        pops.append(pop_list3)
        pops.append(pop_list4)       
    plot_vals(pop_plot, pops, [75,105], "Population", True)

    totalss = [totals_list1, totals_list2]
    if plot_market:
        totalss.append(totals_list3)
        totalss.append(totals_list4)       
    plot_vals(totals_plot, totalss, title="Total Pucks Collected")

    avgpps = [avgpp1, avgpp2]
    if plot_market:
        avgpps.append(avgpp3)
        avgpps.append(avgpp4)       
    plot_vals(avgpp_plot, avgpps, title="Avg. Pucks per Agent")

    reds = [red_list1, red_list2]
    if plot_market:
        reds.append(red_list3)
        reds.append(red_list4)       
    plot_vals(red_plot, reds, [0.4,0.6], "Avg. Red Specialization")

    x = [i*5 for i in range(len(avgpp1_full)//5)]
    test_plot.errorbar(x = x, y=[avgpp1[i] for i in x], yerr=[pp1_dev[i] for i in x], alpha=0.2, color='blue')
    test_plot.plot(avgpp1, color='blue')
    test_plot.errorbar(x = x, y=[avgpp2[i] for i in x], yerr=[pp2_dev[i] for i in x], alpha=0.2, color='red')
    test_plot.plot(avgpp2, color='red')
    test_plot.errorbar(x = x, y=[avgpp3[i] for i in x], yerr=[pp3_dev[i] for i in x], alpha=0.2, color='green')
    test_plot.plot(avgpp3, color='green')
    test_plot.errorbar(x = x, y=[avgpp4[i] for i in x], yerr=[pp4_dev[i] for i in x], alpha=0.2, color='orange')
    test_plot.plot(avgpp4, color='orange')
    test_plot.set_title("Avg. Pucks per Agent (w/ St. Dev.)")

    fig = plt.gcf()
    fig.suptitle("Cost/Gain: " + str(keyval))
    plt.show()



def plot_specialization(datastring):

    rawdict = trim_data(datastring) #this dict holds a record for each agent
    #rawdict[i] = all data for agent #i, organized by generation
    specDict = {}
    genDict = {}

    #this loop needs to be fixed
    for i in range(len(rawdict[0])):
        genDict[i] = genDict.get(i, [])
        genDict[i].extend( [rawdict[j][i][0] 
                                                for j in range(len(rawdict.keys())) 
                                                if rawdict[j][i][0] != -1 
                                                if rawdict[j][i][4] ])

    # for i in range(len(rawdict.keys())):
    #     #comment if/else line to drop data when agent is dead
    #     #comment if line to add dummy value when agent is dead
    #     specDict[i] = [rawdict[j][i][0] 
    #                     if rawdict[j][i][4] else -0.25
    #                     for j in range(len(rawdict.keys()))
    #                     #if rawdict[i][j][4] 
    #                     #if rawdict[i][j][0] != -1
    #                     ]

        #specDict contains all of the agents' specializations at each generation
    index = int(len(genDict.keys()) /2)

    for i in range(len(genDict.keys())):
        index = i
        print(len(genDict[index]))
        sns.distplot(genDict[index], bins = [i/8. for i in range(15)], kde=False)
        plt.axis([-0.2,1.4,0,30])
        plt.title("Generation " + str(i))
        plt.xlabel("Specialization")
        plt.ylabel("Number of Agents")
        plt.show()


    # plt.title("Specialization of Agents [Spaghetti Plot]")
    # plt.xlabel("Generation")
    # plt.ylabel("Specialization")

    # plt.show()
    #input("Press Enter to Close.")




def trim_data(datastring):
    '''
    This is a mess of list comps, basically the function takes in the raw data from the text file and converts it into a dictionary
        containing the data for each agent.
    Final form is: datadict[agentIndex] = [ [spec0, totalpucks0, x0, y0, isAlive0] [...] ... ]
    spec0 means proportion red at generation 0, totalpucks0 is total pucks collected at gen 0, etc.
    '''

    datastring = datastring[2:-2]
    newline_splitstring = datastring.split('\n')[2:]
    newline_splitstring[-1] = newline_splitstring[-1] + ']' #I don't know why this bug happens, apparently the last entry ends up one character short
    
    par_splitstring = [newline_splitstring[i][2:-2].split('),(') for i in range(len(newline_splitstring))]

    splitstring = [ [ par_splitstring[i][j].split(',') for j in range(len(par_splitstring[i])) ] for i in range(len(par_splitstring)) ]

    #now we'll convert this into a dictionary for each agent
    datadict = {}
    for i in range( len(splitstring[0]) ): 
        datadict[i] = [ [float(splitstring[gen][i][j]) for j in range(len(splitstring[gen][i]))] for gen in range(len(splitstring)) ]
    
    return datadict

def main():
    parser = argparse.ArgumentParser(description="Plot points from txt file containing data")
    parser.add_argument('fname', type=str, help='Name of file containing datapoints.')
    parser.add_argument('-t', '--totals', type=str, default=None)
    parser.add_argument('-p', '--paths', action='store_true')
    parser.add_argument('-s', '--specialization', action='store_true')
    parser.add_argument('-d', '--debug', action='store_true')

    args = parser.parse_args()

    f = args.fname

    if args.specialization:
        data = open( cwd + "/" + f, 'r' ).read()
        plot_specialization(data)
    elif args.totals is not None:
        #data2 = open( cwd + '/' + args.totals).read()
        plot_totals(args.totals)
    elif args.paths:
        plot_paths(data)
    elif args.debug:
        trim_data(data)

if __name__ == '__main__':
    main()