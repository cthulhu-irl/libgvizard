# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config
# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

import os
import subprocess
from glob import glob


INDEX_RST_TEMPLATE = """
{title}
{title_underlines}

.. toctree::
    :maxdepth: 1

    {index}
"""

DEFAULT_RST_TEMPLATE = """
{title}
{title_underlines}

.. autodoxygenindex::
    :project: {project}

"""

default_title = 'libgvizard documentation'
toc_delim = '\n    '


def make_project_name(path):
    project = path #os.path.dirname(path)
    project = project.replace('/', '__')
    project = project.replace('.hpp', '')

    return project


def create_rst_layout(headers_path, outpath, excludes=[], recprefix=''):
    if outpath in excludes:
        return

    index_file = os.path.join(outpath, 'index.rst')
    if not os.path.exists(index_file):
        files = glob(os.path.join(headers_path, '*.hpp'))
        files = map(lambda x: os.path.split(x)[-1], files)
        files = map(lambda x: x.replace('.hpp', ''), files)

        dirglob = os.path.join(headers_path, '*')
        dirs = (
            d for d in glob(dirglob)
            if os.path.isdir(d) and d not in excludes
        )
        dirs = map(lambda d: os.path.split(d)[-1], dirs)
        dirs = map(lambda d: os.path.join(d, 'index'), dirs)

        indexlst = [*dirs, *files]

        title = recprefix[:]
        title = title or default_title
        index = toc_delim.join(indexlst)

        rst = INDEX_RST_TEMPLATE.format(
            title=title,
            index=index,
            title_underlines=(len(title) * '=')
        )

        with open(index_file, 'w') as f:
            f.write(rst)

    for header_file in glob(os.path.join(headers_path, '*.hpp')):
        if header_file in excludes:
            continue

        _, filename = os.path.split(header_file)

        project = make_project_name(os.path.join(recprefix, filename))

        title = os.path.join(recprefix, filename)
        if not title.endswith('.hpp'):
            title += ' (dir)'

        rst_file = filename.replace('.hpp', '.rst')
        rst_file = os.path.join(outpath, rst_file)

        if os.path.exists(rst_file):
            continue

        rst = DEFAULT_RST_TEMPLATE.format(
            title=title,
            project=project,
            title_underlines=(len(title) * '=')
        )

        with open(rst_file, 'w') as f:
            f.write(rst)

    for path in glob(os.path.join(headers_path, '*')):
        if os.path.isdir(path):
            _, dirname = os.path.split(path)
            new_outpath = os.path.join(outpath, dirname)

            if not os.path.exists(new_outpath):
                os.mkdir(new_outpath)

            newrecprefix = os.path.join(recprefix, dirname)

            create_rst_layout(path, new_outpath, excludes, newrecprefix)


def generate_projects_source_list(headers_path, recprefix=''):
    ret = {}

    for path in glob(os.path.join(headers_path, '*')):
        if os.path.isdir(path):
            _, dirname = os.path.split(path)

            recdir = os.path.join(recprefix, dirname)

            reclst = generate_projects_source_list(path, recdir)

            ret.update(reclst)

        elif os.path.isfile(path) and path.split('.')[-1] == 'hpp':
            _, filename = os.path.split(path)

            path = os.path.join(recprefix, filename)
            project = make_project_name(path)

            abspath = os.path.abspath(os.path.join(headers_dir, path))

            # for some reason breathe only keeps one `project` when
            # there are multiple projects sharing same `path`.
            #
            # os.path.join removes left hand path (so far joined path)
            # when reaches to an absolute path on the right hand.
            #
            # to overcome this bug(?) of breathe, I (ab)used os.path.join
            # and it magically worked. \o/
            #
            # though it's super creepy... :shrugs:
            #
            ret[project] = (path, [abspath])

    return ret


def get_source_files(headers_dir, exclude_paths, depth=0):
    files = []

    for path in glob(os.path.join(headers_dir, '*')):
        if path in exclude_paths:
            continue

        if path.endswith('.hpp') and os.path.isfile(path):
            files.append((path, depth))

        if os.path.isdir(path):
            files.extend(get_source_files(path, exclude_paths, depth+1))

    return files


def create_root_rst(title, headers_dir, basepath, indexpath, exclude_paths):
    files = []
    dirs = []
    for path, depth in get_source_files(headers_dir, exclude_paths):
        if depth > 1:
            path = path.lstrip(headers_dir)
            dirname, _ = os.path.split(path)
            path = os.path.join(dirname, 'index')

            if path not in dirs:
                dirs.append(path)

            continue

        path = path.lstrip(headers_dir)
        path = path.replace(".hpp", "")

        files.append(path)

    dirs.sort()
    files.sort()

    index = toc_delim.join([*dirs, *files])

    rst = INDEX_RST_TEMPLATE.format(
        title=title,
        title_underlines=len(title) * '=',
        index=index
    )

    with open(indexpath, 'w') as f:
        f.write(rst)


def configure_doxy_file(input_dir, output_dir):

    with open('Doxyfile.in', 'r') as file:
        filedata = file.read()

        filedata = filedata.replace('@DOXYGEN_INPUT_DIR@', input_dir)
        filedata = filedata.replace('@DOXYGEN_OUTPUT_DIR@', output_dir)

    with open('Doxyfile', 'w') as file:
        file.write(filedata)


headers_dir = '../include/gvizard'
exclude_paths = [
    '../include/gvizard/gvizard.hpp',
    '../include/gvizard/colors.hpp',
    '../include/gvizard/attrs.hpp'
]

breathe_projects_source = generate_projects_source_list(headers_dir)
print('\n'.join(f'{k}: {v}' for k, v in breathe_projects_source.items()))

# create rst manual files
create_rst_layout(headers_dir, 'rstfiles', exclude_paths, '')

#create_root_rst(
#    'libgvizard abstract/generic graphviz library',
#    headers_dir,
#    'gvizard',
#    'index.rst',
#    exclude_paths
#)

# Check if we're running on Read the Docs' servers
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

breathe_projects = {}
if read_the_docs_build:
    input_dir = headers_dir
    output_dir = 'build'
    configure_doxy_file(input_dir, output_dir)
    subprocess.call('doxygen', shell=True)
    breathe_projects['libgvizard'] = output_dir + '/xml'


# -- Project information -------------------------------------------------

project = 'libgvizard'
copyright = '2022, Mohsen MK'
author = 'Mohsen MK'


# -- General configuration -----------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.

extensions = ['breathe']  # , 'exhale']

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

primary_domain = 'cpp'
highlight_language = 'cpp'

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Breathe Configuration
breathe_default_project = 'libgvizard'

exhale_args = {
    # These arguments are required
    "containmentFolder":     "./gvizard",
    "rootFileName":          "index.rst",
    "rootFileTitle":         "libgvizard generic graph library",
    "doxygenStripFromPath":  "../include/",
    # Suggested optional arguments
    "createTreeView":        False,
    # TIP: if using the sphinx-bootstrap-theme, you need
    # "treeViewIsBootstrap": True,
    "exhaleExecutesDoxygen": False,
    "exhaleDoxygenStdin":    "INPUT = ../include"
}
