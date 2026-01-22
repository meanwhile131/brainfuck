project('brainfuck', 'c')
executable('interpreter', 'interpreter.c')

test_cases = {
    'hello_world': {'input': '', 'expected': 'Hello World!\n'},
    'io': {'input': '\n', 'expected': 'LK\nLK\n'},
    'array_size': {'input': '', 'expected': '#\n'},
    'common_problems': {'input': '', 'expected': 'H\n'},
    'unmatched_[': {'input': '', 'expected': ''},
    'unmatched_]': {'input': '', 'expected': ''},
    'rot13': {'input': '~mlk zyx', 'expected': '~zyx mlk'},
    'array_lbound': {'input': '', 'expected': ''},
}

foreach name, data : test_cases
    test(name,
        files('test.py'),
        args: [files('tests/@0@.b'.format(name)),
                data['input'], data['expected']]
    )
endforeach