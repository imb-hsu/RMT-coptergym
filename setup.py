from setuptools import setup, find_packages

# Nur die Kern-Abhängigkeiten, die zum Ausführen des Pakets benötigt werden
# Entwickler-Tools wie ipykernel gehören hier nicht zwingend rein.
install_requires = [
    'gymnasium>=0.29.0',
    'numpy>=1.26.0',
    'stable-baselines3>=2.2.0',
    'sb3-contrib>=2.2.0',
    'matplotlib' # Falls du direkt im Paket plotten willst
]

setup(
    name='rmt_coptergym',
    version='0.1.0',
    description='A Gymnasium environment for comparing drone controllers.',
    author='Mark Tappe',
    package_dir={'': 'src'},
    packages=find_packages(where='src'),
    install_requires=install_requires,
)