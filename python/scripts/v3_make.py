# -*- coding: utf-8 -*-
"""Render the detailed beginner-friendly 10-week plan (v0.3)."""

from docx import Document
from docx.shared import Cm, Pt, RGBColor
from docx.enum.text import WD_ALIGN_PARAGRAPH, WD_BREAK
from docx.enum.table import WD_TABLE_ALIGNMENT
from docx.oxml import OxmlElement
from docx.oxml.ns import qn

from v3_data import GLOSSARY, WEEKS, RESOURCES, INTERVIEW_BANK, FIRST_WEEK

OUT = "编程实习10周详细执行手册_v0.3_2026-10-19.docx"

NAVY = RGBColor(0x1F, 0x38, 0x64)
BLUE = RGBColor(0x2E, 0x54, 0x96)
GRAY = RGBColor(0x59, 0x59, 0x59)
LIGHT_GRAY = RGBColor(0x7F, 0x7F, 0x7F)
WHITE = RGBColor(0xFF, 0xFF, 0xFF)
ORANGE = RGBColor(0xC5, 0x5A, 0x11)
CN_FONT = "PingFang SC"
LATIN_FONT = "Arial"
NUMBER_COUNTER = [0]


def set_run_font(run, size=10.5, bold=False, color=None, italic=False):
    run.font.name = LATIN_FONT
    run.font.size = Pt(size)
    run.font.bold = bold
    run.font.italic = italic
    if color is not None:
        run.font.color.rgb = color
    rpr = run._element.get_or_add_rPr()
    rfonts = rpr.find(qn("w:rFonts"))
    if rfonts is None:
        rfonts = OxmlElement("w:rFonts")
        rpr.append(rfonts)
    rfonts.set(qn("w:ascii"), LATIN_FONT)
    rfonts.set(qn("w:hAnsi"), LATIN_FONT)
    rfonts.set(qn("w:eastAsia"), CN_FONT)


def set_para_format(p, before=0, after=4, line=1.32, align=None, left_indent=None):
    pf = p.paragraph_format
    pf.space_before = Pt(before)
    pf.space_after = Pt(after)
    pf.line_spacing = line
    if align is not None:
        p.alignment = align
    if left_indent is not None:
        pf.left_indent = Cm(left_indent)


def shade_cell(cell, hex_color):
    tc_pr = cell._tc.get_or_add_tcPr()
    shd = OxmlElement("w:shd")
    shd.set(qn("w:val"), "clear")
    shd.set(qn("w:color"), "auto")
    shd.set(qn("w:fill"), hex_color)
    tc_pr.append(shd)


def set_cell_margins(cell, top=60, start=80, bottom=60, end=80):
    tc = cell._tc
    tc_pr = tc.get_or_add_tcPr()
    tc_mar = tc_pr.first_child_found_in("w:tcMar")
    if tc_mar is None:
        tc_mar = OxmlElement("w:tcMar")
        tc_pr.append(tc_mar)
    for tag, value in (("w:top", top), ("w:start", start), ("w:bottom", bottom), ("w:end", end)):
        node = tc_mar.find(qn(tag))
        if node is None:
            node = OxmlElement(tag)
            tc_mar.append(node)
        node.set(qn("w:w"), str(value))
        node.set(qn("w:type"), "dxa")


def set_table_borders(table, color="D9E2F3", size=5):
    tbl_pr = table._tbl.tblPr
    borders = OxmlElement("w:tblBorders")
    for edge in ("top", "left", "bottom", "right", "insideH", "insideV"):
        el = OxmlElement(f"w:{edge}")
        el.set(qn("w:val"), "single")
        el.set(qn("w:sz"), str(size))
        el.set(qn("w:space"), "0")
        el.set(qn("w:color"), color)
        borders.append(el)
    tbl_pr.append(borders)


def set_col_widths(table, widths):
    table.autofit = False
    tbl = table._tbl
    tbl_pr = tbl.tblPr
    tbl_w = tbl_pr.find(qn("w:tblW"))
    if tbl_w is None:
        tbl_w = OxmlElement("w:tblW")
        tbl_pr.append(tbl_w)
    tbl_w.set(qn("w:w"), str(int(sum(widths) * 567)))
    tbl_w.set(qn("w:type"), "dxa")
    layout = tbl_pr.find(qn("w:tblLayout"))
    if layout is None:
        layout = OxmlElement("w:tblLayout")
        tbl_pr.append(layout)
    layout.set(qn("w:type"), "fixed")
    grid = tbl.tblGrid
    for i, w in enumerate(widths):
        if i < len(grid.gridCol_lst):
            grid.gridCol_lst[i].set(qn("w:w"), str(int(w * 567)))
    for row in table.rows:
        for i, w in enumerate(widths):
            if i < len(row.cells):
                row.cells[i].width = Cm(w)
        tr_pr = row._tr.get_or_add_trPr()
        if tr_pr.find(qn("w:cantSplit")) is None:
            tr_pr.append(OxmlElement("w:cantSplit"))


def add_paragraph(doc, text="", size=10.5, bold=False, color=None, italic=False,
                  before=0, after=4, line=1.32, align=None, left_indent=None):
    p = doc.add_paragraph()
    set_para_format(p, before=before, after=after, line=line, align=align, left_indent=left_indent)
    if text:
        r = p.add_run(text)
        set_run_font(r, size=size, bold=bold, color=color, italic=italic)
    return p


def add_rich(doc, parts, before=0, after=4, line=1.32):
    p = doc.add_paragraph()
    set_para_format(p, before=before, after=after, line=line)
    for text, bold, color in parts:
        r = p.add_run(text)
        set_run_font(r, size=10.5, bold=bold, color=color)
    return p


def add_heading_cn(doc, text, level=1):
    NUMBER_COUNTER[0] = 0
    p = doc.add_paragraph()
    if level == 1:
        set_para_format(p, before=14, after=6, line=1.15)
        r = p.add_run(text)
        set_run_font(r, size=15.5, bold=True, color=NAVY)
        p_pr = p._p.get_or_add_pPr()
        p_bdr = OxmlElement("w:pBdr")
        bottom = OxmlElement("w:bottom")
        bottom.set(qn("w:val"), "single")
        bottom.set(qn("w:sz"), "8")
        bottom.set(qn("w:space"), "3")
        bottom.set(qn("w:color"), "1F3864")
        p_bdr.append(bottom)
        p_pr.append(p_bdr)
    elif level == 2:
        set_para_format(p, before=10, after=4, line=1.2)
        r = p.add_run(text)
        set_run_font(r, size=12, bold=True, color=BLUE)
    else:
        set_para_format(p, before=7, after=3, line=1.2)
        r = p.add_run(text)
        set_run_font(r, size=11, bold=True, color=RGBColor(0x33, 0x33, 0x33))
    p.paragraph_format.keep_with_next = True
    p.paragraph_format.keep_together = True
    return p


def add_bullet(doc, text, bold_prefix=None, size=10.3, after=2):
    p = doc.add_paragraph(style="List Bullet")
    set_para_format(p, before=0, after=after, line=1.28, left_indent=0.55)
    if bold_prefix:
        r = p.add_run(bold_prefix)
        set_run_font(r, size=size, bold=True)
    r = p.add_run(text)
    set_run_font(r, size=size)
    return p


def add_check(doc, text, size=9.8):
    p = doc.add_paragraph()
    set_para_format(p, before=0, after=2, line=1.28, left_indent=0.55)
    p.paragraph_format.first_line_indent = Cm(-0.55)
    r = p.add_run("□ ")
    set_run_font(r, size=size)
    r = p.add_run(text)
    set_run_font(r, size=size)
    return p


def add_numbered(doc, text, bold_prefix=None, size=10.3, after=2):
    NUMBER_COUNTER[0] += 1
    p = doc.add_paragraph()
    set_para_format(p, before=0, after=after, line=1.28, left_indent=0.6)
    p.paragraph_format.first_line_indent = Cm(-0.6)
    r = p.add_run(f"{NUMBER_COUNTER[0]}. ")
    set_run_font(r, size=size)
    if bold_prefix:
        r = p.add_run(bold_prefix)
        set_run_font(r, size=size, bold=True)
    r = p.add_run(text)
    set_run_font(r, size=size)
    return p


def add_callout(doc, title, body, fill="FFF4E5", border="C55A11", size=9.8):
    table = doc.add_table(rows=1, cols=1)
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = True
    tr_pr = table.rows[0]._tr.get_or_add_trPr()
    tr_pr.append(OxmlElement("w:cantSplit"))
    cell = table.cell(0, 0)
    shade_cell(cell, fill)
    set_cell_margins(cell, top=90, start=130, bottom=90, end=130)
    tc_pr = cell._tc.get_or_add_tcPr()
    borders = OxmlElement("w:tcBorders")
    for edge, sz in (("top", "4"), ("bottom", "4"), ("right", "4"), ("left", "24")):
        el = OxmlElement(f"w:{edge}")
        el.set(qn("w:val"), "single")
        el.set(qn("w:sz"), sz)
        el.set(qn("w:space"), "0")
        el.set(qn("w:color"), border if edge == "left" else "F2D3B5")
        borders.append(el)
    tc_pr.append(borders)
    p1 = cell.paragraphs[0]
    set_para_format(p1, after=2, line=1.22)
    r = p1.add_run(title)
    set_run_font(r, size=10.2, bold=True, color=ORANGE)
    p2 = cell.add_paragraph()
    set_para_format(p2, after=0, line=1.28)
    r = p2.add_run(body)
    set_run_font(r, size=size, color=RGBColor(0x40, 0x40, 0x40))
    doc.add_paragraph().paragraph_format.space_after = Pt(1)


def add_table(doc, headers, rows, widths, font_size=8.6, first_col_bold=False, align_center=False):
    table = doc.add_table(rows=1, cols=len(headers))
    table.alignment = WD_TABLE_ALIGNMENT.CENTER
    table.autofit = False
    set_table_borders(table)
    hdr = table.rows[0]
    for i, h in enumerate(headers):
        cell = hdr.cells[i]
        shade_cell(cell, "1F3864")
        set_cell_margins(cell)
        p = cell.paragraphs[0]
        set_para_format(p, after=0, line=1.1,
                        align=WD_ALIGN_PARAGRAPH.CENTER if align_center else WD_ALIGN_PARAGRAPH.LEFT)
        r = p.add_run(h)
        set_run_font(r, size=font_size, bold=True, color=WHITE)
    for ridx, row in enumerate(rows):
        cells = table.add_row().cells
        for i, val in enumerate(row):
            cell = cells[i]
            if ridx % 2 == 1:
                shade_cell(cell, "EEF3FA")
            set_cell_margins(cell)
            p = cell.paragraphs[0]
            set_para_format(p, after=0, line=1.18,
                            align=WD_ALIGN_PARAGRAPH.CENTER if (align_center and i > 0) else WD_ALIGN_PARAGRAPH.LEFT)
            r = p.add_run(str(val))
            set_run_font(r, size=font_size, bold=(first_col_bold and i == 0))
    set_col_widths(table, widths)
    tr_pr = table.rows[0]._tr.get_or_add_trPr()
    if tr_pr.find(qn("w:tblHeader")) is None:
        tr_pr.append(OxmlElement("w:tblHeader"))
    return table


def add_footer(section, text):
    footer = section.footer
    p = footer.paragraphs[0]
    p.alignment = WD_ALIGN_PARAGRAPH.CENTER
    r = p.add_run(text + "   ·   第 ")
    set_run_font(r, size=8.5, color=LIGHT_GRAY)
    run = p.add_run()
    set_run_font(run, size=8.5, color=LIGHT_GRAY)
    fld1 = OxmlElement("w:fldChar"); fld1.set(qn("w:fldCharType"), "begin")
    instr = OxmlElement("w:instrText"); instr.set(qn("xml:space"), "preserve"); instr.text = "PAGE"
    fld2 = OxmlElement("w:fldChar"); fld2.set(qn("w:fldCharType"), "end")
    run._r.append(fld1); run._r.append(instr); run._r.append(fld2)
    r2 = p.add_run(" 页")
    set_run_font(r2, size=8.5, color=LIGHT_GRAY)


# ---------------- document ----------------
doc = Document()
section = doc.sections[0]
section.page_width = Cm(21.0)
section.page_height = Cm(29.7)
section.top_margin = Cm(1.9)
section.bottom_margin = Cm(1.8)
section.left_margin = Cm(2.2)
section.right_margin = Cm(2.2)

style = doc.styles["Normal"]
style.font.name = LATIN_FONT
style.font.size = Pt(10.3)
style.element.rPr.rFonts.set(qn("w:eastAsia"), CN_FONT)

add_footer(section, "编程实习 10 周详细执行手册 · v0.3")

# Cover
for _ in range(2):
    add_paragraph(doc, "", after=0)
add_paragraph(doc, "编程实习 10 周 · 详细执行手册", size=12, bold=True, color=BLUE, after=6)
add_paragraph(doc, "西安理工大学 · 人工智能 · 大二", size=15, bold=True, color=NAVY, after=4)
add_paragraph(doc, "6 小时/天", size=26, bold=True, color=NAVY, after=6)
add_paragraph(doc, "从“只会基础语法”到“能上手做项目”", size=15, bold=False, color=NAVY, after=8)
p = doc.add_paragraph()
set_para_format(p, after=12, line=1.2)
r = p.add_run("零基础友好版：每个术语先讲人话，每周给题号、文件名、命令和验收清单")
set_run_font(r, size=10.8, color=GRAY)

add_callout(doc,
            "怎么用这本手册",
            "不要一次读完。每周只看本周那一节；术语表当字典，不用背；每天按“今日 6 小时”执行，完成就打勾。"
            "卡住超过 20 分钟，先看“卡住怎么办”，再问 DSH 要提示，不要死磕。",
            fill="EAF1FB", border="2E5496")

meta = doc.add_table(rows=5, cols=2)
meta.alignment = WD_TABLE_ALIGNMENT.CENTER
meta.autofit = False
set_table_borders(meta, color="D9E2F3", size=4)
meta_rows = [
    ("你的目标", "2026 年 12 月 31 日前，拿到一段能远程/在西安持续写代码的日常实习"),
    ("你的投入", "每天 6 小时起步；6 天/周；10.5 周约 380 小时"),
    ("主项目", "Python + FastAPI + RAG（能演示、能评测、能部署）"),
    ("C++ 定位", "LeetCode 用 C++；另做一个 Top-K 向量检索 CLI（多线程 + 基准）"),
    ("版本", "v0.3 · 2026-10-19 · 详细执行版"),
]
for i, (k, v) in enumerate(meta_rows):
    c0, c1 = meta.rows[i].cells
    shade_cell(c0, "F2F5FA")
    set_cell_margins(c0); set_cell_margins(c1)
    p0 = c0.paragraphs[0]; set_para_format(p0, after=0, line=1.2)
    r0 = p0.add_run(k); set_run_font(r0, size=9.3, bold=True, color=NAVY)
    p1 = c1.paragraphs[0]; set_para_format(p1, after=0, line=1.2)
    r1 = p1.add_run(v); set_run_font(r1, size=9.3, color=GRAY)
set_col_widths(meta, [3.0, 12.8])

doc.add_paragraph().add_run().add_break(WD_BREAK.PAGE)

# 0. how to use / learning loop
add_heading_cn(doc, "零、先学会“怎么学”：一份通用学习流程", 1)
add_paragraph(doc, "你不需要先成为“很厉害的人”才能开始。你需要的是一套不骗自己的学习流程。下面这套流程适用于任何知识点：")
add_heading_cn(doc, "0.1 五步学习闭环", 2)
add_numbered(doc, "先看 5–10 分钟的概念/文档/视频，不求全懂，只求知道它在解决什么问题。", bold_prefix="看：")
add_numbered(doc, "关掉资料，用自己的话写 3 句解释；写不出来就说明还没懂。", bold_prefix="写：")
add_numbered(doc, "写一个 10–30 行的最小例子，跑通；再改一个参数，看结果怎么变。", bold_prefix="跑：")
add_numbered(doc, "故意弄坏它（删一行、传错类型、断网），看报错，再修好。", bold_prefix="坏：")
add_numbered(doc, "讲给 DSH/同学听，让它挑错；然后做 1–2 道题或加一个小功能。", bold_prefix="讲：")

add_heading_cn(doc, "0.2 不同类型知识点的具体学法", 2)
add_table(doc, ["类型", "怎么学", "怎么算学会"], [
    ("概念（API/HTTP/ORM/索引）", "看 1 篇官方文档或 1 个 10 分钟视频 → 写 3 句人话 → 举一个生活例子 → 在项目里找它", "能不用术语、用生活例子讲给外行听"),
    ("代码/框架（FastAPI/SQLAlchemy）", "抄最小例子跑通 → 改一个参数 → 弄坏 → 看报错 → 修好 → 写一个测试", "能独立从空目录搭出最小可运行版本"),
    ("算法题", "自己试 20 分钟 → 看题解 → 关掉重写 → 总结模板 → 第二天再做一遍", "能不看题解写出同类题，并能说复杂度"),
    ("项目", "画数据流图 → 写伪代码 → 最小版本 → 加一个功能 → 测试 → 部署", "陌生人按 README 能跑；你能讲 5 分钟"),
    ("八股", "定义 → 原理 → 项目例子 → 取舍", "能绑定自己的项目，而不是背标准答案"),
], widths=[3.4, 8.2, 4.8], font_size=8.6, first_col_bold=True)

add_heading_cn(doc, "0.3 卡住时的处理顺序", 2)
add_numbered(doc, "先读报错最后一行，查关键词；不要从头读整段报错。")
add_numbered(doc, "把问题缩到最小：10 行能复现吗？不能就继续缩。")
add_numbered(doc, "问 DSH：“不要直接给答案，先给我 3 个排查方向/提示。”")
add_numbered(doc, "超过 30 分钟仍无进展：跳过，记录到问题库，晚上统一问/查。")
add_numbered(doc, "每周日回看问题库，把重复出现的 3 个问题搞懂。")

add_heading_cn(doc, "0.4 问 DSH 的 6 个万能提示词", 2)
add_table(doc, ["场景", "直接复制这句话"], [
    ("看不懂概念", "用 12 岁能懂的话解释【概念】，给一个生活类比，再给一个 10 行以内的代码例子。"),
    ("看不懂报错", "把这段报错翻译成人话，列出 3 个最可能原因，按概率排序；先别给完整修复。"),
    ("检查理解", "我说一遍我的理解，你指出哪里对、哪里错、漏了什么；不要客气。"),
    ("代码审查", "审查这段代码：正确性、边界、复杂度、可读性；只给最小修改，不要重写。"),
    ("出题", "根据我刚学的【知识点】出 5 道由浅入深的题，先别给答案；我做完你再批改。"),
    ("模拟面试", "你是后端面试官，一次问 1 题，追问 3 层，最后按 1–5 分打分并给改进建议。"),
], widths=[3.2, 13.2], font_size=8.8, first_col_bold=True)

# 1. glossary
add_heading_cn(doc, "一、术语速查：看不懂的词，先来这里", 1)
add_paragraph(doc, "下面这些词会反复出现。不用背，遇到时回来查；每个词只记“人话”那一列。")
add_table(doc, ["术语", "人话（一句话）", "你会在哪里用到"],
          [(a, b, c) for a, b, c in GLOSSARY],
          widths=[3.0, 9.2, 4.2], font_size=8.2, first_col_bold=True)

# 2. ten-week overview
add_heading_cn(doc, "二、10 周总表：每周只盯 3 件事", 1)
overview = [
    ("W0", "10/19–10/25", "诊断 + 环境 + 方向", "诊断报告、GitHub、看板", "3 个诊断任务"),
    ("W1", "10/26–11/01", "Python + FastAPI + SQL", "小 API + 10 题", "8 个测试/README"),
    ("W2", "11/02–11/08", "RAG 后端骨架", "上传/列表/删除 + 8 测试", "12 题"),
    ("W3", "11/09–11/15", "切分/向量/检索/回答", "RAG 主链路 + 5 问", "12 题"),
    ("W4", "11/16–11/22", "引用/评测/Docker", "RAG v1 + 20 条评测", "12 题"),
    ("W5", "11/23–11/29", "C++ Top-K + 打磨", "C++ CLI + 基准", "10 题"),
    ("W6", "11/30–12/06", "简历 + 投递", "简历 v1 + 50 投", "12 题"),
    ("W7", "12/07–12/13", "八股 + 算法 + 投递", "20 问答 + 75 投", "12 题"),
    ("W8", "12/14–12/20", "面试冲刺", "100 投 + 3 面", "10 题"),
    ("W9", "12/21–12/27", "复盘 + 补弱", "简历 v2 + 125 投", "10 题"),
    ("W10", "12/28–12/31", "收尾 + Plan B", "offer/Plan B", "8 题"),
]
add_table(doc, ["周", "日期", "主题", "关键产出", "验收"], overview,
          widths=[1.0, 3.0, 4.4, 5.0, 3.0], font_size=8.4, first_col_bold=True)

add_callout(doc,
            "如果时间不够，按这个顺序砍",
            "① 项目加分项（PDF/多轮/混合检索/rerank）→ ② 算法 hard → ③ CS 冷门章节 → ④ 投递？永远不要砍投递。"
            "每周至少保：3 天项目、5 天算法、1 次投递/复盘。",
            fill="FFF4E5")

# 3. weekly detail
add_heading_cn(doc, "三、逐周执行：每天做什么、做哪题、交什么", 1)
add_paragraph(doc, "每周 6 天执行，周日复盘。每天 6 小时 = 算法 1.5h + CS 1h + 项目 3h + 晚上 0.5h。"
                   "“学会的标准”比“看了多少”重要；完不成验收，不要开下一周。刷题前先看附录 A 的题型小抄：每题先判断属于哪一类，再动手。")
add_callout(doc,
            "时间不够时的优先级",
            "项目 > 算法 > 投递 > CS 理论；但 W6 起投递不能砍。每天至少 1 道新题 + 1 道复习；"
            "一道题超过 45 分钟没思路就直接看题解，不要硬耗到 2 小时。",
            fill="FFF4E5")

for wk in WEEKS:
    add_heading_cn(doc, f"{wk['id']}（{wk['date']}）{wk['title']}", 2)
    add_rich(doc, [("本周目标：", True, BLUE), (wk["goal"], False, None)], after=3)

    add_heading_cn(doc, "本周要搞懂的 3 个概念", 3)
    add_table(doc, ["概念", "人话解释", "怎么学（看什么 + 动手）", "学会的标准"],
              wk["concepts"], widths=[2.4, 5.0, 5.2, 3.8], font_size=8.0, first_col_bold=True)

    add_heading_cn(doc, "每天做什么（6 小时）", 3)
    add_table(doc, ["天", "算法 1.5h", "CS / 概念 1h", "项目 3h", "晚上 0.5h"],
              wk["days"], widths=[1.2, 3.0, 3.4, 6.9, 1.9], font_size=7.9, first_col_bold=True)

    add_heading_cn(doc, "本周题目（LeetCode 题号）", 3)
    add_table(doc, ["题号", "题目", "难度", "练什么"],
              [(n, name, diff, focus) for n, name, diff, focus in wk["problems"]],
              widths=[1.2, 7.0, 1.6, 6.6], font_size=8.0, first_col_bold=True)

    add_heading_cn(doc, "本周交付物（完成打勾）", 3)
    for item in wk["deliverables"]:
        add_check(doc, item)

    add_heading_cn(doc, "自检 8 问（答不出就回看）", 3)
    for q in wk["selfcheck"]:
        add_check(doc, q)

    add_callout(doc, "如果卡住 / 时间不够", wk["skip"], fill="FFF4E5", size=9.3)

# 4. project breakdown
add_heading_cn(doc, "四、主项目拆解：按模块做，不要一上来写完整系统", 1)
add_paragraph(doc, "RAG 项目看起来大，其实只有 6 个模块。每个模块先做最小版本，跑通再加下一个。"
                   "不要把“学完 RAG 再做”当前提；你是“做一个模块，学一个概念”。")

add_heading_cn(doc, "4.1 模块顺序与验收", 2)
add_table(doc, ["模块", "你要写什么", "输入/输出", "验收"], [
    ("1. 上传", "POST /documents；保存 md/txt；限制大小/类型", "文件 → 文件路径 + 数据库记录", "上传后 GET /documents 能看到"),
    ("2. 切分", "chunk.py：按标题/段落切，带 overlap", "长文本 → 多个 chunk（含 doc_id）", "打印前 3 个 chunk，长度合理"),
    ("3. 向量化", "embed.py：调 embedding API，存 numpy/pgvector", "chunk → 向量", "同一句话两次向量几乎一样"),
    ("4. 检索", "search.py：余弦相似度/Top-K", "问题向量 → 最像的 K 个 chunk", "问 5 个问题，至少 3 个命中正确文档"),
    ("5. 回答", "answer.py：拼 prompt，要求引用", "问题 + chunks → 答案 + 引用", "答案下面能看到文件名/片段"),
    ("6. 评测", "20 条 QA，算 Recall@5/P95", "QA + 检索结果 → 指标", "report.md 有数字和失败案例"),
], widths=[2.2, 6.8, 4.6, 2.8], font_size=8.2, first_col_bold=True)

add_heading_cn(doc, "4.2 建议目录结构", 2)
add_table(doc, ["文件/目录", "作用"], [
    ("app/main.py", "FastAPI 入口，注册路由"),
    ("app/models.py", "SQLAlchemy 模型（Document/Chunk）"),
    ("app/schemas.py", "Pydantic 请求/响应模型"),
    ("app/db.py", "数据库连接/Session"),
    ("rag/chunk.py", "切分函数"),
    ("rag/embed.py", "embedding 调用与缓存"),
    ("rag/search.py", "Top-K 检索"),
    ("rag/answer.py", "拼 prompt、调 LLM、返回引用"),
    ("tests/test_api.py", "上传/列表/删除/问答测试"),
    ("eval/qa.jsonl", "20 条评测问题 + 正确文档"),
    ("eval/report.md", "Recall@5/P95/成本/失败案例"),
    ("Dockerfile / compose.yaml", "部署"),
    ("README.md", "架构图、启动、接口、评测"),
], widths=[4.6, 11.8], font_size=8.6, first_col_bold=True)

add_heading_cn(doc, "4.3 C++ Top-K 小项目 5 步", 2)
add_numbered(doc, "读向量文件（文本/二进制），存成 vector<vector<float>>；先做 1000 条小数据。")
add_numbered(doc, "写 cosine 暴力版 + partial_sort，确认 Top-K 结果正确。")
add_numbered(doc, "按行分块给 std::thread，每个线程算局部 Top-K，最后合并；用 mutex 保护结果。")
add_numbered(doc, "加 CMake、-O2、-Wall -Wextra；写 README 和命令行参数。")
add_numbered(doc, "跑 1M×128 维基准：单线程 vs 4 线程，记录耗时/加速比/内存；写进 README。")

# 5. job
add_heading_cn(doc, "五、求职执行：简历、投递、面试", 1)
add_heading_cn(doc, "5.1 简历模板（1 页）", 2)
add_table(doc, ["区块", "写什么", "示例"], [
    ("头部", "姓名/电话/邮箱/GitHub/城市/可实习时间", "西安/远程 · 每周 5 天 · 可连续 6 个月"),
    ("教育", "学校/专业/年级/时间", "西安理工大学 · 人工智能 · 大二 · 2024–2028"),
    ("技能", "语言/框架/数据库/工具", "C++（STL/多线程）、Python、FastAPI、SQL、Docker、Git"),
    ("项目 1", "RAG 3–4 条 bullet，含指标", "Recall@5 85%、P95 1.5s、Docker 部署"),
    ("项目 2", "C++ Top-K 3 条 bullet，含加速比", "1M×128，4 线程 3.2×，CMake"),
    ("其他", "LeetCode/开源/博客（只写有证据的）", "LeetCode 110 题；GitHub 链接"),
], widths=[2.2, 6.6, 7.6], font_size=8.3, first_col_bold=True)

add_heading_cn(doc, "5.2 投递渠道与节奏", 2)
add_table(doc, ["渠道", "怎么用", "优先级"], [
    ("Boss 直聘", "筛“实习 + 远程/西安”；每天 10–15 家；打招呼带 GitHub", "高"),
    ("实习僧", "按城市/远程筛；适合中小公司", "高"),
    ("牛客", "看面经、投递、找内推；注意发布时间", "高"),
    ("电鸭社区/远程社区", "远程岗位、外包、开源协作", "中"),
    ("GitHub/开源", "给 RAG/LLM 项目提 PR；维护者可能给远程机会", "中"),
    ("学校/老师/学长", "西安理工 AI 实验室、就业中心、内推", "中"),
    ("公司官网", "AI 创业公司 careers 页；比平台直接", "中"),
], widths=[3.2, 10.6, 2.6], font_size=8.4, first_col_bold=True)
add_paragraph(doc, "节奏：W6 每天 10 家 → W7 15 家 → W8–W9 15 家；累计 100–150。每投 10 家记录一次反馈；5–7 天没回可跟进一次。",
              size=9.3, color=GRAY)

add_heading_cn(doc, "5.3 Boss 打招呼模板", 2)
add_callout(doc,
            "直接复制，改成你的信息",
            "您好，我是西安理工大学人工智能专业大二学生，C++/Python 双栈，做过一个带引用和评测的 RAG 问答服务，"
            "以及一个 C++ 多线程 Top-K 检索 CLI。可远程、每周 5 天、能连续实习 6 个月，期望 3–6 个月的日常实习。"
            "附件是 GitHub 和 3 分钟 demo，方便的话想投递贵司的 AI 应用/后端实习。",
            fill="FFF4E5")

add_heading_cn(doc, "5.4 面试题库（20 题，先自己答）", 2)
add_table(doc, ["问题", "答题要点"], INTERVIEW_BANK,
          widths=[6.0, 10.4], font_size=8.2, first_col_bold=True)

# 6. first week
add_heading_cn(doc, "六、第一周超详细清单（照着做）", 1)
add_paragraph(doc, "这一周不要想“我要学完 Python”，只做下面的事。每天结束打勾；没做完的周日补，不超过 2 小时。")
for day, items in FIRST_WEEK:
    add_heading_cn(doc, day, 3)
    for item in items:
        add_check(doc, item)

# 7. resources
add_heading_cn(doc, "七、资源清单：只看这些，不要收藏 50 门课", 1)
add_table(doc, ["类别", "具体资源", "用在哪周"], RESOURCES,
          widths=[3.0, 10.6, 2.8], font_size=8.3, first_col_bold=True)
add_callout(doc,
            "资源使用规则",
            "每个知识点最多 1 个主资源 + 官方文档；视频 1.5 倍速，只看当前任务需要的 10–20 分钟；"
            "看完必须写 3 句 + 跑一个例子，否则等于没看。",
            fill="EAF1FB")

# 8. weekly review template
add_heading_cn(doc, "八、每周复盘模板（周日 30 分钟）", 1)
add_table(doc, ["问题", "写什么"], [
    ("本周产出", "项目/题数/投递数/面试数（只写事实）"),
    ("最大卡点", "一个具体问题，不要写“算法不好”"),
    ("下周 3 件事", "按优先级，不超过 3 件"),
    ("要砍掉什么", "没必要的课程/功能/题"),
    ("需要 DSH 帮什么", "一个具体问题，下周问"),
], widths=[4.0, 12.4], font_size=8.8, first_col_bold=True)

add_heading_cn(doc, "九、最后三句话", 1)
add_numbered(doc, "你不需要先“准备好”才开始；你需要在做的过程中变好。")
add_numbered(doc, "每周只盯 3 件事：一个能跑的产出、一组题、一次投递/复盘。")
add_numbered(doc, "12/31 不是生死线；大二的时间窗口很长，先上车，再换车。")

# Appendix A
add_heading_cn(doc, "附录 A：算法题型小抄（刷题前先看）", 1)
add_paragraph(doc, "每道题先判断“它属于哪一类”，再套步骤。下面 16 类覆盖了本周计划里的绝大多数题；看不懂的术语回第一章查。")
add_table(doc, ["题型", "人话 + 什么时候用", "模板 / 步骤", "对应题"], [
    ("双指针", "两个下标一起走；有序数组、两端、去重、链表。", "left=0, right=n-1；while left<right；根据条件移动一边。", "27/977/344/11/15"),
    ("滑动窗口", "连续子数组/子串，求最长/最短。", "right 扩张；不满足时 left 收缩；每步更新答案。", "209/3/438/239"),
    ("哈希", "快速判断出现过/计数/两数之和。", "dict/set 存见过的值；边遍历边查。", "1/242/349/560"),
    ("前缀和", "多次求区间和/子数组和。", "pre[i]=pre[i-1]+a[i]；区间和=pre[r]-pre[l-1]。", "560"),
    ("栈", "括号/相邻消除/表达式/单调。", "遇左入栈；遇右弹出比较；单调栈存下标。", "20/1047/150/239"),
    ("链表", "反转/合并/环/倒数第 k。", "画图；哑节点 dummy；先存 next 再改指针；快慢指针。", "206/24/19/160/141/142"),
    ("二叉树递归", "深度/路径/对称/祖先。", "终止条件；递归左右；合并结果。", "104/101/226/236"),
    ("BFS", "层序/最短步数/腐烂/岛屿。", "queue；while queue；pop；邻居入队；记录层数。", "102/994/200"),
    ("DFS", "连通块/岛屿/路径。", "visited；递归四个方向；先判边界。", "200/207"),
    ("回溯", "组合/排列/子集/分割。", "路径 push；终止收集；遍历选择；递归；pop。", "77/46/78/131"),
    ("二分", "有序/找边界/插入位置。", "left/right；mid；根据条件缩半；注意 left<=right 和边界。", "704/35/34"),
    ("贪心", "每步选眼前最好；区间/跳跃/分发。", "排序；局部最优；用例子验证。", "455/55/45/134"),
    ("动态规划", "计数/最优/背包/字符串。", "定义 dp[i]；写转移；初始化；定遍历顺序；举例验证。", "70/62/322/198"),
    ("堆 / Top-K", "前 K/最大最小/流。", "维护 size=K 的堆；比堆顶就替换。", "215/347/239"),
    ("图 / 拓扑", "依赖/课程表。", "算入度；入度 0 入队；弹出减邻居；计数。", "207"),
    ("位运算", "只出现一次/异或。", "a^a=0，a^0=a；成对抵消。", "136"),
], widths=[2.2, 5.2, 5.6, 3.4], font_size=8.0, first_col_bold=True)
add_callout(doc,
            "刷题的正确顺序",
            "先判断题型 → 写 3 行思路 → 自己写 20 分钟 → 看题解 → 关掉重写 → 总结模板 → 第二天再做一遍。"
            "不要一上来就看答案，也不要在同一道题上耗 2 小时。",
            fill="EAF1FB")

# Appendix B
add_heading_cn(doc, "附录 B：Python 基础 3 天补课（如果 W1 跟不上）", 1)
add_paragraph(doc, "如果你连 Python 的 for、函数、类都写不顺，不要硬上 W1；先花 3 天做下面的事，再开始。项目顺延 3 天，W10 用申请/面试补回来。")
add_table(doc, ["天", "学什么", "动手练习（必须自己写）", "算过关"], [
    ("Day 1", "变量/类型/if/for/函数", "九九乘法表；判断素数；统计一段文字的单词频次", "能不看资料写出 30 行"),
    ("Day 2", "list/dict/set/文件/JSON", "读写 JSON；列表去重；统计成绩并排序", "能解释 list 和 dict 区别"),
    ("Day 3", "类/异常/模块/venv", "定义 Book 类；写一个 CLI 待办；建 venv 装 requests", "能独立建项目并运行"),
], widths=[1.8, 5.4, 6.8, 2.4], font_size=8.4, first_col_bold=True)
add_callout(doc,
            "过关标准",
            "能独立写一个 50 行的 CLI：读 JSON、增删改查、处理文件不存在/参数错误。写不出来就再练 1 天，不要急着做 RAG。",
            fill="FFF4E5")

# Appendix C
add_heading_cn(doc, "附录 C：每周复盘模板（可打印）", 1)
add_table(doc, ["问题", "本周填写"], [
    ("本周产出", "项目/题数/投递数/面试数"),
    ("最大卡点", "一个具体问题（不要写“算法不好”）"),
    ("下周 3 件事", "按优先级，不超过 3 件"),
    ("要砍掉什么", "没必要的课程/功能/题"),
    ("需要 DSH 帮什么", "一个具体问题，下周问"),
], widths=[4.2, 12.2], font_size=8.8, first_col_bold=True)

add_heading_cn(doc, "附录 D：常用命令小抄", 1)
add_paragraph(doc, "这些命令会反复用。不用背，复制后改路径；每条都亲手跑一次。")
add_table(doc, ["场景", "命令", "说明"], [
    ("建虚拟环境", "python3 -m venv .venv", "在项目根目录建 .venv"),
    ("激活（macOS/Linux）", "source .venv/bin/activate", "命令行前出现 (.venv)"),
    ("激活（Windows）", ".venv\\Scripts\\activate", "PowerShell 用 .venv\\Scripts\\Activate.ps1"),
    ("装依赖", "pip install fastapi uvicorn pytest", "装到当前 venv"),
    ("冻结依赖", "pip freeze > requirements.txt", "记录版本，部署用"),
    ("跑 API", "uvicorn main:app --reload", "默认 127.0.0.1:8000，/docs 看接口"),
    ("跑测试", "pytest -q", "-q 只显示结果"),
    ("Git 初始化", "git init && git add . && git commit -m \"init\"", "第一次提交"),
    ("Git 推送", "git remote add origin <url> && git push -u origin main", "推到 GitHub"),
    ("看状态/日志", "git status / git log --oneline", "改了什么/提交历史"),
    ("SQLite", "sqlite3 app.db", ".tables / .schema；或 DB Browser"),
    ("curl GET", "curl http://127.0.0.1:8000/health", "调接口"),
    ("curl POST", "curl -X POST http://127.0.0.1:8000/tasks -H \"Content-Type: application/json\" -d '{\"title\":\"test\"}'", "发 JSON"),
    ("Docker 构建/运行", "docker build -t rag-api . && docker run -p 8000:8000 rag-api", "镜像/容器"),
    ("Compose", "docker compose up --build", "起 api + db"),
    ("看端口占用", "lsof -i :8000", "macOS/Linux；Windows 用 netstat -ano | findstr 8000"),
    ("C++ 编译", "g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o topk", "先能编译再写 CMake"),
    ("CMake", "cmake -B build && cmake --build build", "生成并构建"),
], widths=[3.2, 8.8, 4.4], font_size=7.9, first_col_bold=True)

doc.save(OUT)
print("saved", OUT)
