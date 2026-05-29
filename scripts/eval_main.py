import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.dirname(script_dir)

# Ensure local script modules are importable
sys.path.insert(0, script_dir)
sys.path.insert(0, os.path.join(script_dir, 'evaluation_utils'))
sys.path.insert(0, os.path.join(project_root, 'src'))

from evaluation_utils import evaluation_data
from evaluation_utils import evaluation_plots


def main():
    print('Running eval_main: evaluation_data followed by evaluation_plots')

    evaluation_data.main()
    evaluation_plots.main()


if __name__ == '__main__':
    main()
