import os
import sys

script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.dirname(script_dir)

sys.path.insert(0, script_dir)
sys.path.insert(0, os.path.join(project_root, 'src'))

from data_gen import main as data_gen_main
from eval_indi_baseline import main as eval_indi_main


def main():
    print('Running initial setup: data_gen then eval_indi_baseline')
    data_gen_main()
    eval_indi_main()


if __name__ == '__main__':
    main()
