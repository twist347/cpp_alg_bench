#!/usr/bin/env python
"""Script to visualize google-benchmark output with interactive plots"""
from __future__ import print_function
import argparse
import sys
import logging
import pandas as pd
import plotly.graph_objects as go

logging.basicConfig(format='[%(levelname)s] %(message)s')

METRICS = ['real_time', 'cpu_time', 'bytes_per_second', 'items_per_second']
TRANSFORMS = {
    '': lambda x: x,
    'inverse': lambda x: 1.0 / x
}


def get_default_ylabel(args):
    """Compute default ylabel for commandline args"""
    label = ''
    if args.transform == '':
        label = args.metric
    else:
        label = args.transform + '(' + args.metric + ')'

    if args.metric == 'real_time':
        label += ' (ms)'

    if args.relative_to is not None:
        label += ' relative to %s' % args.relative_to
    return label

def parse_args():
    """Parse commandline arguments"""
    parser = argparse.ArgumentParser(
        description='Visualize google-benchmark output')
    parser.add_argument(
        '-f', metavar='FILE', type=argparse.FileType('r'), default=sys.stdin,
        dest='file', help='path to file containing the csv benchmark data')
    parser.add_argument(
        '-m', metavar='METRIC', choices=METRICS, default=METRICS[0], dest='metric',
        help='metric to plot on the y-axis, valid choices are: %s' % ', '.join(METRICS))
    parser.add_argument(
        '-t', metavar='TRANSFORM', choices=TRANSFORMS.keys(), default='',
        help='transform to apply to the chosen metric, valid choices are: %s'
             % ', '.join(list(TRANSFORMS)), dest='transform')
    parser.add_argument(
        '-r', metavar='RELATIVE_TO', type=str, default=None,
        dest='relative_to', help='plot metrics relative to this label')
    parser.add_argument(
        '--xlabel', type=str, default='input size', help='label of the x-axis')
    parser.add_argument(
        '--ylabel', type=str, help='label of the y-axis')
    parser.add_argument(
        '--title', type=str, default='', help='title of the plot')
    parser.add_argument(
        '--logx', action='store_true', help='plot x-axis on a logarithmic scale')
    parser.add_argument(
        '--logy', action='store_true', help='plot y-axis on a logarithmic scale')

    args = parser.parse_args()
    if args.ylabel is None:
        args.ylabel = get_default_ylabel(args)
    return args


def parse_input_size(name):
    splits = name.split('/')
    if len(splits) == 1:
        return 1
    return int(splits[1])


def read_data(args):
    """Read and process dataframe using commandline args"""
    try:
        data = pd.read_csv(args.file, usecols=['name', args.metric])
    except ValueError:
        msg = 'Could not parse the benchmark data. Did you forget "--benchmark_format=csv"?'
        logging.error(msg)
        exit(1)
    data['label'] = data['name'].apply(lambda x: x.split('/')[0])
    data['input'] = data['name'].apply(parse_input_size)
    data[args.metric] = data[args.metric].apply(TRANSFORMS[args.transform])
    return data


def plot_groups(label_groups, args):
    """Display the processed data"""
    fig = go.Figure()
    for label, group in label_groups.items():
        fig.add_trace(go.Scatter(
            x=group.index,
            y=group[args.metric],
            mode='lines+markers',
            name=label
        ))

    if args.logx:
        fig.update_xaxes(type='log')
    if args.logy:
        fig.update_yaxes(type='log')

    fig.update_layout(
        title=args.title,
        xaxis_title=args.xlabel,
        yaxis_title=args.ylabel,
        legend_title="Labels",
        legend=dict(x=0, y=1, traceorder='normal', orientation='h')
    )

    fig.show()


def main():
    """Entry point of the program"""
    args = parse_args()
    data = read_data(args)
    label_groups = {}
    for label, group in data.groupby('label'):
        label_groups[label] = group.set_index('input', drop=False)
    if args.relative_to is not None:
        try:
            baseline = label_groups[args.relative_to][args.metric].copy()
        except KeyError as key:
            msg = 'Key %s is not present in the benchmark output'
            logging.error(msg, str(key))
            exit(1)

    if args.relative_to is not None:
        for label in label_groups:
            label_groups[label][args.metric] /= baseline
    plot_groups(label_groups, args)


if __name__ == '__main__':
    main()
