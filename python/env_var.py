def get_env_vars(command, only_changed=True):
    """
    Source variables from a shell script
    import them in the environment (if update==True)
    and report only the script variables (if clean==True)
    """

    if only_changed:
        environ_back = dict(os.environ)
        os.environ.clear()

    pipe = Popen("exec bash -c '%s; env'" % command, stdout=PIPE, shell=True)
    data = pipe.communicate()[0]
    env = dict((line.split("=", 1) for line in data.splitlines()))

    if only_changed:
        # remove unwanted minimal vars
        env.pop('LINES', None)
        env.pop('COLUMNS', None)
        os.environ = dict(environ_back)

    return env
