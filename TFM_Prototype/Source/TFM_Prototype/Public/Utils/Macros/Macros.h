#pragma once

#define PRINT(Format, ...) \
	if (GEngine) \
	{ \
		FString Str1 = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
		FString Str2 = GetClass()->GetName(); \
		FString Text = Str1 + TEXT("   <<") + Str2 + TEXT(">>"); \
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Text, false, FVector2D(1.1, 1.1)); \
	}



#define PRINT_K(key, Format, ...) \
	if (GEngine) \
	{ \
		FString Str1 = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
		FString Str2 = GetClass()->GetName(); \
		FString Text = Str1 + TEXT("   <<") + Str2 + TEXT(">>"); \
		GEngine->AddOnScreenDebugMessage(key, 5.0f, FColor::Red, Text, false, FVector2D(1.1, 1.1)); \
	}



#define PRINT_T(seconds, Format, ...) \
	if (GEngine) \
	{ \
		FString Str1 = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
		FString Str2 = GetClass()->GetName(); \
		FString Text = Str1 + TEXT("   <<") + Str2 + TEXT(">>"); \
		GEngine->AddOnScreenDebugMessage(-1, seconds, FColor::Red, Text, false, FVector2D(1.1, 1.1)); \
	}


