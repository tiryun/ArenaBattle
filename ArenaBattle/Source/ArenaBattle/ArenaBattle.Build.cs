// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ArenaBattle : ModuleRules
{
	public ArenaBattle(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "WebService" }); //WebService를 쓰겠다라고 표시, 이렇게 하면 UBT에서 자동으로 WebService모듈을 ArenaBattle모듈보다 먼저 로딩 

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
