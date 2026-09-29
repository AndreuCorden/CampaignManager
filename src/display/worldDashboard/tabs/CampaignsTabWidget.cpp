#include "CampaignsTabWidget.h"
#include "../cards-dropzone/CampaignDropZone.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

CampaignsTabWidget::CampaignsTabWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(12, 12, 12, 12);

    QHBoxLayout *header = new QHBoxLayout();
    QLabel *title = new QLabel("Campaigns Set in This World", this);
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #D4AF37;");
    
    QPushButton *newCampaignBtn = new QPushButton("+ New Campaign", this);
    newCampaignBtn->setCursor(Qt::PointingHandCursor);
    newCampaignBtn->setStyleSheet(
        "QPushButton { padding: 6px 14px; background-color: #D4AF37; color: #1A202C; border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #ECC94B; }"
    );

    header->addWidget(title);
    header->addStretch();
    header->addWidget(newCampaignBtn);
    mainLayout->addLayout(header);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContent = new QWidget(scrollArea);
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);

    // Active Section
    QLabel *activeHeader = new QLabel("Active Campaigns (Drag here to reactivate)", scrollContent);
    activeHeader->setStyleSheet("font-size: 14px; font-weight: bold; color: #E2E8F0; margin-top: 8px;");
    contentLayout->addWidget(activeHeader);

    CampaignDropZone *activeDropZone = new CampaignDropZone(scrollContent);
    m_activeLayout = activeDropZone->contentLayout();
    contentLayout->addWidget(activeDropZone);

    // Archived Section
    QLabel *archivedHeader = new QLabel("Archived Campaigns (Drag here to archive)", scrollContent);
    archivedHeader->setStyleSheet("font-size: 14px; font-weight: bold; color: #A0AEC0; margin-top: 16px;");
    contentLayout->addWidget(archivedHeader);

    CampaignDropZone *archivedDropZone = new CampaignDropZone(scrollContent);
    m_archivedLayout = archivedDropZone->contentLayout();
    contentLayout->addWidget(archivedDropZone);

    contentLayout->addStretch();
    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    connect(newCampaignBtn, &QPushButton::clicked, this, &CampaignsTabWidget::createCampaignRequested);
    connect(activeDropZone, &CampaignDropZone::campaignDropped, this, &CampaignsTabWidget::reactivateCampaignRequested);
    connect(archivedDropZone, &CampaignDropZone::campaignDropped, this, &CampaignsTabWidget::archiveCampaignRequested);
}