#include "MainFrame.h"
#include<wx/wx.h>
#include<vector>
#include"Task.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	CreateControls();
	BindEventHandlers();
}

void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 24)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "TO DO LIST", wxPoint(0, 22), wxSize(800, -1), 
		wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);
	headlineText->SetBackgroundColour(*wxRED);

	inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 80), wxSize(495, 35), wxTE_PROCESS_ENTER);
	addbutton = new wxButton(panel, wxID_ANY, "add", wxPoint(600, 80), wxSize(100, 35)); 
	checklistbox = new wxCheckListBox(panel, wxID_ANY, wxPoint(100, 120), wxSize(600, 400));
	clearbutton = new wxButton(panel, wxID_ANY, "clear", wxPoint(100, 525), wxSize(100, 35));

}

void MainFrame::BindEventHandlers()
{
	addbutton->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
	inputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::OnInputEnter, this);
	checklistbox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnListKeyDown, this);
	clearbutton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);




}

void MainFrame::OnButtonClicked(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

void MainFrame::OnInputEnter(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

void MainFrame::OnListKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
	case WXK_DELETE:
		DeleteSelectedTask();
		break;
	case WXK_UP:
		MoveSelectedTask(-1);
	case WXK_DOWN:
		MoveSelectedTask(1);
		break;

	}
}

void MainFrame::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (checklistbox->IsEmpty()) {
		return;}

	wxMessageDialog	dialog(this, "you sure you wanna exit , son ?", "clear", wxYES_NO | wxCANCEL);

	int result = dialog.ShowModal();
	if (result == wxID_YES) {
		checklistbox->Clear();
	}
}

void MainFrame::AddTaskFromInput()
{
	wxString description = inputField->GetValue();
	
	if (!description.IsEmpty()) {
		checklistbox->Insert(description, checklistbox->GetCount());
		inputField->Clear();
	}
	inputField->SetFocus();
}

void MainFrame::DeleteSelectedTask()
{
	int SelectedIndex = checklistbox->GetSelection();

	if (SelectedIndex == wxNOT_FOUND) {
		return;
	}
	checklistbox->Delete(SelectedIndex);
}

void MainFrame::MoveSelectedTask(int offset)
{
	int SelectedIndex = checklistbox->GetSelection();

	if (SelectedIndex == wxNOT_FOUND) {
		return;}
	int newIndex = SelectedIndex + offset;

	if (newIndex >= 0 && newIndex < checklistbox->GetCount()); {
		SwapTask(SelectedIndex, newIndex);
		checklistbox->SetSelection(newIndex, true);

	}
}

void MainFrame::SwapTask(int i, int j)
{
	Task taskI{ checklistbox->GetString(i).ToStdString(),checklistbox->IsChecked(i) };
	Task taskJ{ checklistbox->GetString(j).ToStdString(),checklistbox->IsChecked(j) };

	checklistbox->SetString(i, taskJ.description);
	checklistbox->Check(i, taskJ.done);
	

	checklistbox->SetString(j, taskI.description);
	checklistbox->Check(j,taskI.done);


	
}
