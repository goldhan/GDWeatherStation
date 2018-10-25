import urwid

edit = urwid.Edit('请输入')


button = urwid.Button('退出程序')

pile = urwid.Pile([edit,button])

fill = urwid.Filler(pile,'top')
def exitBtn(button):
    raise urwid.ExitMainLoop()

urwid.connect_signal(button,'click',exitBtn)


loop = urwid.MainLoop(fill)
loop.run()