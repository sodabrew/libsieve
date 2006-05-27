<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>

<!-- $title =) -->
<head>
<title>{$title}</title>
<link rel="stylesheet" title="code" href="code.css">
</head>

<basefont face="lucida">
<body bgcolor="#ffffff" link="#0050a0" vlink="#0050a0" alink="#000000" marginheight="0" marginwidth="0">

<table width="100%" border=0 cellspacing=0 cellpadding=0>
	<tr>
	<td bgcolor="#000000">
		<table width="100%" border=0 cellspacing=2 cellpadding=0>
			<tr>
			<td bgcolor="#305080">
				<font color="#ffffff" size="+4"><b>
				&nbsp;{$lefthead}&nbsp;
				</b></font>
			</td>
			<td width="100%" bgcolor="#d0d0d0">
				<font size="+4"><b>
				&nbsp;{$righthead|spacify}
				</b></font>
			</td>
			</tr>
			<tr>
			<td bgcolor="#000000" colspan=2>
				<font color="#808080"><small><b>
				&nbsp;&nbsp;
				{assign var=i value=0}
				{foreach from=$toplinks item=link}
					{if $i != 0} &nbsp;&nbsp;|&nbsp;&nbsp;
					{else} {assign var=i value=1} {/if}
					{if $link[1] == $thispage}
						<font color="#ffffff">{$link[0]|spacify}</font>
					{else}
						<a href="{$link[1]}"><font color="#c0c0c0">{$link[0]|spacify}</font></a>
					{/if}
				{/foreach}
				</b></small></font>
			</td>
			</tr>
		</table>
	</td>
	</tr>
	<tr>
	<td valign=top colspan=2>

		<table width="100%" border=0 cellspacing=4 cellpadding=0>
			<tr>
			<td width="100%">

				<table width="100%" border=0 cellspacing=0 cellpadding=4>
					<tr>
					<td width="66%" valign=top>

					<table width="100%" border=0 cellspacing=0 cellpadding=0>
					<tr><td bgcolor=#000000>

						<table width="100%" border=0 cellspacing=2 cellpadding=2 cols=2>
							<tr>
							<td bgcolor=#305080 nowrap>
								<b><font color=#ffffff>
									{$lefttitle|spacify}
								</font></b>
							</td>
							<td bgcolor=#484848>
								&nbsp;
							</td>
							</tr>
							<tr>
							<td colspan=2 bgcolor=#d0d0d0>
							{foreach from=$leftcontent item=content}
								{if $content[0] != ""}
									<b>{$content[0]}</b>
									<br>
								{/if}
								<!--small-->
								{$content[1]}
								<!--/small-->
								<br><br>
							{/foreach}
							</td>
						</table>

						</td></tr>
						</table>

					</td>
					<td width="33%" valign=top>

						<table width="100%" border=0 cellspacing=0 cellpadding=0>
						<tr><td bgcolor=#000000>

						<table width="100%" border=0 cellspacing=2 cellpadding=2 cols=2>
							<tr>
							<td bgcolor=#305080 nowrap>
								<b><font color=#ffffff>
									{$righttitle|spacify}
								</font></b>
							</td>
							<td bgcolor=#484848>
								&nbsp;
							</td>
							</tr>
							<tr>
							<td bgcolor=#d0d0d0 colspan=2>
							{assign var=i value=0}
							{foreach from=$rightcontent item=content}
								{if $i != 0} <br> <br>
								{else} {assign var=i value=1} {/if}
								{if $content[0] != ""}
									<b>{$content[0]}</b>
									<br>
								{/if}
								<small>
								{$content[1]}
								</small>
							{/foreach}
							{assign var=i value=0}
							{foreach from=$rightlinks item=link}
								{if $i != 0} <br> <br>
								{else} {assign var=i value=1} {/if}
								{if $link[1] == $thispage}
									<b>{$link[0]}</b> {$link[2]}
								{else}
									<b><a href="{$link[1]}">{$link[0]}</a></b> {$link[2]}
								{/if}
							{/foreach}
							<br>
							</td>
						</table>

						</td></tr>
						</table>

						<br>

						<table width="100%" border=0 cellspacing=0 cellpadding=0>
						<tr><td bgcolor=#000000>

						<table width="100%" border=0 cellspacing=2 cellpadding=2 cols=2>
							<tr>
							<td bgcolor=#305080 nowrap>
								<b><font color=#ffffff>
									l i n k s .
								</font></b>
							</td>
							<td bgcolor=#484848>
								&nbsp;
							</td>
							</tr>
							<tr>
							<td bgcolor=#d0d0d0 colspan=2>
							{assign var=i value=0}
							{foreach from=$links item=link}
								{if $i != 0} <br> <br>
								{else} {assign var=i value=1} {/if}
								{if $link[1] == $thispage}
									<b>{$link[0]}</b> {$link[2]}
								{else}
									<b><a href="{$link[1]}">{$link[0]}</a></b> {$link[2]}
								{/if}
							{/foreach}
							</td>
						</table>

						</td></tr>
						</table>

					</td>
					</tr>
				</table>

			</td>
			<td>
			</td>
			</tr>
		</table>

	</td>
	</tr>
</table>

<small><center>
	template &copy; 2002 by artwiz of <a href="http://www.oswd.org/">oswd</a> -- contents &copy; 2002, 2003 by aaron stone
</center></small>

</body></html>
