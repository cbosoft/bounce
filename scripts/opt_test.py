import numpy as np
from matplotlib import pyplot as plt


def opt_iterate(f, lb, ub, thresh):
    span = ub - lb
    n = int(span*10/thresh)
    dx = span/n
    x = lb
    rv = [np.abs(f(x))]
    for i in range(n):
        x += dx
        if x > ub: x = ub
        if x < lb: x = lb
        y = np.abs(f(x))
        rv.append(y)
        if y < thresh:
            break
    return rv


def opt_graddesc(f, lb, ub, thresh):
    span = ub - lb
    m = 0.5
    dx = span*m
    x = lb
    py = np.abs(f(x))
    rv = [py]
    for i in range(1000):
        x += dx
        if x > ub: x = ub
        if x < lb: x = lb
        y = np.abs(f(x))
        dy = y - py
        py = y
        rv.append(y)
        if y < thresh:
            break
        if dy >= 0.0:
            dx *= -m
    return rv


def opt_graddesc_quarter(f, lb, ub, thresh):
    span = ub - lb
    m = 0.25
    dx = span*m
    x = lb
    py = np.abs(f(x))
    rv = [py]
    for i in range(1000):
        x += dx
        if x > ub: x = ub
        if x < lb: x = lb
        y = np.abs(f(x))
        dy = y - py
        py = y
        rv.append(y)
        if y < thresh:
            break
        if dy >= 0.0:
            dx *= -m
    return rv


def opt_graddesc_tenth(f, lb, ub, thresh):
    span = ub - lb
    m = 0.1
    dx = span*m
    x = lb
    py = np.abs(f(x))
    rv = [py]
    for i in range(1000):
        x += dx
        if x > ub: x = ub
        if x < lb: x = lb
        y = np.abs(f(x))
        dy = y - py
        py = y
        rv.append(y)
        if y < thresh:
            break
        if dy >= 0.0:
            dx *= -m
    return rv


def test_opt(f, s, thresh):
    return f(*s, thresh)


if __name__ == '__main__':
    optimisers = [
        (opt_iterate, 'iterate'),
        (opt_graddesc, 'gradient descent (-1/2)'),
        (opt_graddesc_quarter, 'gradient descent (-1/4)'),
        (opt_graddesc_tenth, 'gradient descent (-1/10)'),
    ]
    scenarios = [
        (lambda x: x, -1.0, 1.0, 'line'),
        (lambda x: 1.0-np.sqrt(1.0 - x**2), -1.0, 1.0, 'circle'),
        (lambda x: 0.5-np.sqrt(1.0 - x**2), -1.0, 1.0, 'circle/2'),
        (lambda x: 0.25-np.sqrt(1.0 - x**2), -1.0, 1.0, 'circle/4'),
    ]

    plt.figure(figsize=(10, 6))
    thresh = 5e-3
    for i, (opt, opt_name) in enumerate(optimisers):
        worst = test_opt(opt, scenarios[0][:-1], thresh)
        worst_name = scenarios[0][-1]
        best = worst
        best_name = worst_name
        for scenario in scenarios[1:]:
            scenario_name = scenario[-1]
            y = test_opt(opt, scenario[:-1], thresh)
            if len(y) > len(worst):
                worst = y
                worst_name = scenario_name
            if len(y) < len(best):
                best = y
                best_name = scenario_name
        plt.plot(np.arange(len(worst))+1, worst,
                 label=f'{opt_name} ({worst_name})', color=f'C{i}')
        # plt.plot(np.arange(len(best))+1, best, '--',
        #          label=f'{opt_name} ({best_name})', color=f'C{i}')

    plt.xlabel('n')
    plt.ylabel('y')
    plt.yscale('log')
    plt.xscale('log')

    plt.axhline(thresh, ls='--', color='k')

    plt.legend(loc='center left', bbox_to_anchor=(1.02, 0.5), bbox_transform=plt.gca().transAxes)
    plt.tight_layout()
    plt.savefig('out.pdf')