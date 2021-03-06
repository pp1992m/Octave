/*

Copyright (C) 2013-2017 Torsten

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

Octave is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

// Author: Torsten <ttl@justmail.de>

#if ! defined (octave_octave_qscintilla_h)
#define octave_octave_qscintilla_h 1

#include <Qsci/qsciscintilla.h>
#include <QMenu>
#include <QContextMenuEvent>

class octave_qscintilla : public QsciScintilla
{
  Q_OBJECT

public:

  octave_qscintilla (QWidget *p);
  ~octave_qscintilla ();

  enum
    {
      ST_NONE = 0,
      ST_LINE_COMMENT,
      ST_BLOCK_COMMENT
    };

  virtual void contextMenuEvent (QContextMenuEvent *e);

  void context_help_doc (bool);
  void context_edit ();
  void context_run ();
  void get_global_textcursor_pos (QPoint *global_pos, QPoint *local_pos);
  bool get_actual_word ();
  void clear_indicator (int indicator_style);
  void get_current_position (int *pos, int *line, int *col);
  QString comment_string ();
  int get_style (int pos = -1);
  int is_style_comment (int pos = -1);

signals:

  void execute_command_in_terminal_signal (const QString&);
  void create_context_menu_signal (QMenu*);
  void context_menu_edit_signal (const QString&);
  void qsci_has_focus_signal (bool);
  void status_update (bool,bool);
  void show_doc_signal (const QString&);
  void context_menu_break_condition_signal (int);
  void context_menu_break_once (int);

private slots:

  void contextmenu_help (bool);
  void contextmenu_doc (bool);
  void contextmenu_help_doc (bool);
  void contextmenu_edit (bool);
  void contextmenu_run (bool);

  void contextmenu_break_condition (bool);
  void contextmenu_break_once (const QPoint&);

  void text_changed (void);

protected:

  void focusInEvent (QFocusEvent *focusEvent);

private:

  QString _word_at_cursor;

};

#endif
